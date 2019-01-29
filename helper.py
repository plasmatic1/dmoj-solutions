import os
import shutil
import configparser

# Configuration Constants

CFG_NAME = 'helper_cfg.ini'
cfg_file = configparser.ConfigParser()
cfg_file.read_file(open(CFG_NAME))

CPP_SECTION = 'cpp'
JAVA_SECTION = 'java' # yava
PY_SECTION = 'py'
GLOBAL_SECTION = 'global'

SRC_KEY = 'SrcDir'
DEST_KEY = 'DestDir'
ENABLED_KEY = 'Enabled'

OVERWRITE_KEY = 'Overwrite'

# Constants

def parse_bool_str(bool_str):
    return True if bool_str == 'True' else False

CPP_SRC_DIR = cfg_file[CPP_SECTION][SRC_KEY]
CPP_DIR = cfg_file[CPP_SECTION][DEST_KEY]
CPP_ENABLED = parse_bool_str(cfg_file[CPP_SECTION][ENABLED_KEY])

JAVA_SRC_DIR = cfg_file[JAVA_SECTION][SRC_KEY]
JAVA_DIR = cfg_file[JAVA_SECTION][DEST_KEY]
JAVA_ENABLED = parse_bool_str(cfg_file[JAVA_SECTION][ENABLED_KEY])

PY_SRC_DIR = cfg_file[PY_SECTION][SRC_KEY]
PY_DIR = cfg_file[PY_SECTION][DEST_KEY]
PY_ENABLED = parse_bool_str(cfg_file[PY_SECTION][ENABLED_KEY])

OVERWRITE_FILES = parse_bool_str(cfg_file[GLOBAL_SECTION][OVERWRITE_KEY])

# Functions

def copy(loca, locb):
    shutil.copy(loca, locb)

def walk(src_dir, dest_dir, path_factory):
    for project in os.listdir(src_dir):
        begin, dest = path_factory(src_dir, dest_dir, project)
    
        if not os.path.isfile(begin):
            continue

        print('Copying project "%s"' % project)
        
        if (not OVERWRITE_FILES) and os.path.isfile(dest):
            print('File overwrite is disabled! Copying aborted!')
            continue

        copy(begin, dest)

# File Name Factories

def cpp_file_factory(src_dir, dest_dir, project):
    file_name = '%s.cpp' % project

    return '%s\\%s\\src\\%s' % (src_dir, project, file_name), '%s\\%s' % (dest_dir, file_name)

def java_py_file_factory(src_dir, dest_dir, project):
    return '%s\\%s' % (src_dir, project), '%s\\%s' % (dest_dir, project)

# Debug

if CPP_ENABLED:
    print('CPP Eclipse directory : "%s"\nCPP directory : "%s"' %
        (CPP_SRC_DIR, CPP_DIR))
else:
    print('CPP is disabled!')

if JAVA_ENABLED:
    print('Java Eclipse directory : "%s"\nCPP directory : "%s"' %
        (JAVA_SRC_DIR, JAVA_DIR))
else:
    print('Java is disabled!')

if PY_ENABLED:
    print('Python Source directory : "%s"\nCPP directory : "%s"' %
        (PY_SRC_DIR, PY_DIR))
else:
    print('PY is disabled!')

# -- Directory walks

if CPP_ENABLED:
    walk(CPP_SRC_DIR, CPP_DIR, cpp_file_factory)

if JAVA_ENABLED:
    walk(JAVA_SRC_DIR, JAVA_DIR, java_py_file_factory)

if PY_ENABLED:
    walk(PY_SRC_DIR, PY_DIR, java_py_file_factory)

# Pause

input('Press enter to continue...')
