from msvcrt import getch
import pymem
from colorama import Fore

def remove_098(string):
    return string.replace(" ", "")

def get_process_by_pid(pid):
        try:
            mem = pymem.Pymem()
            mem.open_process_from_id(pid)
            return mem
        except pymem.exception.ProcessNotFound:
            print(Fore.RED + f"\n(!ERROR!) " + Fore.WHITE + "=" + Fore.GREEN + f" (!Process with PID {pid} not found!)" + Fore.WHITE)
            #imports.own.will_go_to_start.main()
            getch()
            exit(0)

def read_code_from_file(file_path):
        try:
            with open(file_path, 'r') as file:
                return file.read()
        except IOError:
            print(Fore.RED + f"\n(!ERROR!) " + Fore.WHITE + "=" + Fore.GREEN + f" (!Failed to read file at {file_path}!)" + Fore.WHITE)
            #imports.own.will_go_to_start.main()
            getch()
            exit(0)

def inject_code(mem, code):
        try:
            mem.inject_python_interpreter()  ### Injects the Python interpreter to be able to understand Python code
            #print(Fore.GREEN + "Python interpreter injected successfully." + Fore.WHITE)
            
            print(Fore.GREEN + f"\n(!SUCCESS!) " + Fore.WHITE + "=" + Fore.YELLOW + f" (!File injected successfully!)" + Fore.WHITE)
            mem.inject_python_shellcode(code)  ### Injecting the code
            #print(Fore.GREEN + "Code injected successfully." + Fore.WHITE)
            #imports.own.will_go_to_start.main()
            getch()
            exit(0)
        except Exception as e:
            print(Fore.RED + f"\n(!ERROR!) " + Fore.WHITE + "=" + Fore.GREEN + f" (!An error occurred during injection: {e}!)" + Fore.WHITE)
            #imports.own.will_go_to_start.main()
            getch()
            exit(0)
            
def inject_prog_2_start():

    # Input PID and file path
    print(Fore.RED + "Enter 'esc' (for exit)" + Fore.WHITE)        
    file_path = input(Fore.YELLOW + "Enter path to file: " + Fore.WHITE)
    
    if remove_098(file_path.lower()) == "esc":
        #imports.own.will_go_to_start.main()
        exit(0)

    print(Fore.RED + "\nEnter 'esc' (for exit)" + Fore.WHITE)
    pid = input(Fore.YELLOW + "Enter PID to target process: " + Fore.WHITE)
    
    if remove_098(str(pid).lower()) == "esc":
        #imports.own.will_go_to_start.main()
        exit(0) 

    # Get the process
    mem = get_process_by_pid(int(pid))
    if mem is None:
        print(Fore.RED + f"\n(!ERROR!) " + Fore.WHITE + "=" + Fore.GREEN + f" (!Process not found!)" + Fore.WHITE)
        getch()
        exit(0)
        #imports.own.will_go_to_start.main()

    # Read the code from the file
    code = read_code_from_file(file_path)
    if code is None:
        print(Fore.RED + f"\n(!ERROR!) " + Fore.WHITE + "=" + Fore.GREEN + f" (!Failed to read code from file!)" + Fore.WHITE)
        #imports.own.will_go_to_start.main()
        getch()
        exit(0)

    # Inject the code and check for success
    inject_code(mem, code)

inject_prog_2_start()