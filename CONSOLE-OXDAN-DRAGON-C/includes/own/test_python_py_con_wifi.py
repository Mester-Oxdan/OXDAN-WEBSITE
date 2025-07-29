from msvcrt import getch
import pywifi #import
from pywifi import const # const - это некоторые константы, установленные wifi, например, код состояния соответствует 4, сбой равен 0 и т. д.
import time
from colorama import Fore
import os

profile = pywifi.Profile()

def remove_098(string):
    return string.replace(" ", "")

def crack_4(password):

    while True:
            "" "Взломать Wi-Fi" ""
            wifi = pywifi.PyWiFi () # Реализуем объект
            # Получите первую сетевую карту
            iface= wifi.interfaces()[0]
                 # Отключить подключение сетевой карты
            iface.disconnect()
            time.sleep(2)
    
                 # Удалить все файлы конфигурации Wi-Fi (что-то вроде запрета точкам доступа Wi-Fi запоминать нашу информацию об инициализации Lei Shiyu)
            iface.remove_all_network_profiles()
    
                 # Создайте новый файл конфигурации Wi-Fi, укажите файл, имя Wi-Fi, пароль, метод кодирования и другие параметры конфигурации
                 # const.IFACE_DISCONNECTED фактически равно 4, 4 означает, что соединение успешно
            if iface.status() == const.IFACE_DISCONNECTED: 

                profile.auth = const.AUTH_ALG_OPEN
                         # алгоритм шифрования Wi-Fi
                profile.akm.append(const.AKM_TYPE_WPA2PSK)
                profile.cipher = const.CIPHER_TYPE_CCMP
                         # пароль Wi-Fi
                profile.key = password #password здесь пароль, переданный read_password ()

                         # Добавить новый файл конфигурации Wi-Fi
                new_profile = iface.add_network_profile(profile)

                         # Подключить Wi-Fi

                try:
        
                    iface.connect(new_profile)

                except:

                    print(Fore.RED + "(!ERROR!) " + Fore.WHITE + "=" + Fore.GREEN + " (!Wifi name was not found!)\n" + Fore.WHITE)
                    getch()
                    exit(0)

                time.sleep(4)
                if iface.status() == const.IFACE_CONNECTED:
                    #print("\nConnection was " + Fore.GREEN + "successful!" + Fore.WHITE)
		    print(Fore.GREEN + "\n(!SUCCESS!) " + Fore.WHITE + "=" + Fore.YELLOW + " (!Wifi connection successful!)\n" + Fore.WHITE)
                    getch()
                    return True
                else:
                    print(Fore.RED + "\n(!ERROR!) " + Fore.WHITE + "=" + Fore.GREEN + " (!Wifi password or ssid is incorrect!)\n" + Fore.WHITE)
                    getch()
                    return False
                         

def con_wifi_start():

    os.system("cls")
    print(Fore.RED + "\nEnter 'esc' (for exit)")
    ferd = input(Fore.YELLOW + "Enter wifi name: " + Fore.WHITE)

    if remove_098(ferd.lower()) == "esc":
        exit(0)

    print(Fore.RED + "\nEnter 'esc' (for exit)")
    ferd_2 = input(Fore.YELLOW + "Enter wifi password: " + Fore.WHITE)
    if remove_098(ferd_2.lower()) == "esc":
        exit(0)
    try:
        
        profile.ssid = str(ferd)
        crack_4(ferd_2)

    except:

        print(Fore.RED + "\n(!ERROR!) " + Fore.WHITE + "=" + Fore.GREEN + " (!Wifi name was not found!)\n" + Fore.WHITE)
        getch()
        exit(0)

con_wifi_start()
