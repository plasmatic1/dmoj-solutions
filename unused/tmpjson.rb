require 'httparty'

File.open('subs.json', 'w') do |f|
    resp = HTTParty.get 'https://dmoj.ca/api/user/submissions/Plasmatic'
    f << resp.body
end
