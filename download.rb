require 'set'
require 'httparty'
require 'json'

### Constants

# Problem codes to ignore
IGNORE = Set.new ['phantomc1', 'joi14p6', 'acc4p4', 'bbc08d']

# Whether debug mode is on (program will retrieve submission data from local file and session id is a set variable)
DEBUG = false 
DEBUG_SESSION_ID = nil
subs = nil
$session_id = nil

# Amount of time to wait between requests (in seconds).  Helps prevent being cloudflared
REQ_DELAY_TIME = 2

# Mapping language on dmoj to one of the aformentioned languages
LANG_MAP = {
    :JAVA8 => 'java',
    :JAVA9 => 'java',
    :JAVA10 => 'java',
	:JAVA11 => 'java',
	:JAVA15 => 'java',
    
    :PY2 => 'py',
    :PY3 => 'py',
    :PYPY => 'py',
    :PYPY2 => 'py',
    :PYPY3 => 'py',

    :CPP03 => 'cpp',
    :CPP11 => 'cpp',
    :CPP14 => 'cpp',
    :CPP17 => 'cpp',
    :CLANGX => 'cpp',
	
	:PCPP11 => 'cpp',
	:PCPP03 => 'cpp',

    :C => 'c',
    :C11 => 'c',

    :GO => 'go',
    :TEXT => 'txt',
    :NASM => 'nasm',
    :PERL => 'perl',
    :RUBY2 => 'ruby',
}

# List of languages
LANGS = LANG_MAP.map { |k, v| v }.uniq

### Functions

def read_sol(lang, problem_id)
    data = nil
    File.open("#{lang}/#{problem_id}") { |f| data = f.read }
    data
end

def get_submission_src(sub_id)
    resp = HTTParty.get "https://dmoj.ca/src/#{sub_id}/raw", cookies: { :sessionid => $session_id }
    return resp.body.gsub(/\r/, '')
end

### Run code

# Get session id
if DEBUG
    $session_id = DEBUG_SESSION_ID
else
    puts 'Input the session id (can be found by looking at your cookies):'
    $session_id = gets
    puts
end

# Display running parameters
puts "Running program with the following parameters:"
puts "Using session id #{$session_id}"
puts "Using request delay time #{REQ_DELAY_TIME}secs"
puts "Ignoring problems #{IGNORE.to_a}"
puts "Running with languages #{LANGS}"
puts "Debug mode #{DEBUG.to_s.upcase}"
puts

# Get local solutions
puts "Fetching local solutions..."

sols = Hash.new [] 
LANGS.each do |lang|
    dir_path = "./#{lang}"
    if !Dir.exist? dir_path
        puts "Directory for lang #{lang} doesnt exist! Making one..."
        Dir.mkdir dir_path
    end
    sols[lang] = Set.new(Dir.entries(dir_path).map { |file| file.split('.')[0] }.uniq)
end

puts "Fetched local solutions!"
puts

# Get global submissions (only JSON data)
puts "Getting global submissions..."

if DEBUG
    File.open('subs.json') { |f| subs = JSON.parse(f.read) }
else
    resp = HTTParty.get 'https://dmoj.ca/api/user/submissions/Plasmatic'
    subs = JSON.parse(resp.body)
end

puts "Got global submissions!"
puts

# Find missing solutions
puts "Finding missing solutions..."

reqs = Hash.new 
subs.each do |sub_id, sub|
    if sub["result"] == 'AC'
        lang = LANG_MAP[sub["language"].to_sym]
        problem_id = sub["problem"]

        if lang == nil
            puts "Missing language #{sub['language']}! (problem #{problem_id})"
            exit 0
        end

        if !sols[lang].include?(problem_id)
            problem_key = [problem_id, lang]
            if !reqs.include?(problem_key)
                if IGNORE.include? problem_id
                    puts "Ignoring: #{problem_id} in language #{lang}..."
                    next
                else
                    puts "Missing: #{problem_id} in language #{lang}..."
                end
            end
            reqs[problem_key] = sub_id
        end
    end
end

puts

# Making temorary solutions folders (only on debug mode)
if DEBUG
    puts 'Making temorary solution folders... (DEBUG ONLY)'

    if !Dir.exist? 'tmp'
        Dir.mkdir 'tmp'
        puts 'Made root temporary solution folder'
    end

    LANGS.each do |lang|
        path = "tmp/#{lang}"
        if !Dir.exist? path
            Dir.mkdir path
            puts "Made temporary solution folder tmp/#{path}"
        end
    end

    puts
end

# Fetching submissions

puts "Fetching submissions..."

reqs.each do |(problem_id, lang), sub_id|
    src = get_submission_src(sub_id)
    File.open("#{DEBUG ? "tmp/" : ""}#{lang}/#{problem_id}.#{lang}", 'w') do |f|
        f << src
    end

    puts "Fetched #{lang}/#{problem_id} (submission ##{sub_id})"

    sleep(REQ_DELAY_TIME)
end

puts "Fetched all submissions!"
