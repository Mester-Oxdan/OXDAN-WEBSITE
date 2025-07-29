from msvcrt import getch
from colorama import Fore
from googletrans import Translator

def remove_098(string):
    return string.replace(" ", "")

def start():

    try:

            print(" ")
            print(Fore.RED + "Enter 'esc' (for exit)" + Fore.WHITE)
            x = input(Fore.YELLOW + "Enter language from: " + Fore.WHITE)
            if remove_098(x.lower()) == "esc":
                exit(0)

            print(Fore.RED + "\nEnter 'esc' (for exit)" + Fore.WHITE)
            y = input(Fore.YELLOW + "Enter language to: " + Fore.WHITE)
            if remove_098(y.lower()) == "esc":
                exit(0)

            print(Fore.RED + "\nEnter 'esc' (for exit)" + Fore.WHITE)
            z = input(Fore.YELLOW + f"Enter text to translate from {x} to {y}: " + Fore.WHITE)
            if remove_098(z.lower()) == "esc":
                exit(0)

            # Create translator object
            translator = Translator()

            # Translate the entire sentence
            result = translator.translate(z, src=x, dest=y).text

            print(Fore.YELLOW + "Translated text: " + Fore.WHITE + result)
            getch()
            exit(0)
            

    except:

        print(Fore.RED + "\n(!ERROR!) " + Fore.WHITE + "=" + Fore.GREEN + " (!Enter valid languages!)\n" + Fore.WHITE)
        getch()
        exit(0)

start()
