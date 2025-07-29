# track location with the map using the phone number
from msvcrt import getche
from time import sleep
import phonenumbers
from phonenumbers import timezone
from phonenumbers import geocoder
from phonenumbers import carrier
 
import folium
 
from opencage.geocoder import OpenCageGeocode
from phonenumbers.util import u
import pycountry , phonenumbers
from phonenumbers.phonenumberutil import region_code_for_number
from geopy.geocoders import Nominatim
from uszipcode import SearchEngine
from colorama import Fore

def remove_098(string):
    return string.replace(" ", "")

# taking input the phonenumber along with the country code
print(Fore.RED + "Enter 'esc' (for exit)")
number = input(Fore.YELLOW + "Enter Phone Number with country code like (" + Fore.WHITE + "+1.........." + Fore.YELLOW + "): " + Fore.WHITE)

print(Fore.WHITE)

if remove_098(number.lower()) == "esc":
    
    exit(0)

# Parsing the phonenumber string to convert it into phonenumber format
phoneNumber = phonenumbers.parse(number)
 
# Storing the API Key in the Key variable
Key = "4ce6fc5fb55a4e0883a37f1513389bf2" #generate your api https://opencagedata.com/api
 
# Using the geocoder module of phonenumbers to print the Location in console
yourLocation = geocoder.description_for_number(phoneNumber,"en")
region = yourLocation
country = pycountry.countries.get(alpha_2 = region_code_for_number(phoneNumber))
city = "test"
zip_cor = "test"
not_sure = "(No info)"

print(" ") 
print("Country: " + country.name)
sleep(0.01)
print("Region: " + region)
sleep(0.01)
print("City: " + not_sure)
sleep(0.01)
print("Zip: " + not_sure)
sleep(0.01)
print("Y: " + not_sure)
sleep(0.01)
print("X: " + not_sure)
sleep(0.01)

getche()
