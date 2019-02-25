import inspect
import sys

def main():
    # Have to account for unix vs windows
    modulename = sys.argv[0]
    if modulename.count('\\'):
        modulename = modulename.split('\\')[-1].split('.')[0]
    else:
        modulename = modulename.split('/')[-1].split('.')[0]
    
    module = __import__(modulename)
    print(inspect.getsource(module))

if __name__ == '__main__':
    main()