from colorama import Fore
from winotify import Notification, audio
import requests, git, msvcrt
import asyncio
import aiohttp, os

files_dir = os.path.dirname(__file__)
os.environ["OXDAN-DRAGON-PYTHON"] = files_dir 

def update_program():
    try:

            async def fetch_data():
                async with aiohttp.ClientSession() as session:
                    url = "http://raw.githubusercontent.com/Mester-Oxdan/Oxdan-Dragon-C/main/version"
                    async with session.get(url) as response:
                        return await response.text()

            async def main():
                response = await fetch_data()
                #print (response)
                if response != "2.2024\n":
                    message = Notification(app_id="OXDAN-DRAGON-PYTHON",
                                   title="New Update!",
                                   msg="New update available. After login use 'update' command.",
                                   duration="short",
                                   icon=os.path.join(os.environ["OXDAN-DRAGON-PYTHON"],r"my_dragon_ico_transformed.png"))
                                   #icon=r"C:\Users\bogda\Downloads\Oxdan-Dragon-Python\CONSOLE-OXDAN-DRAGON-PYTHON\imports\own\my_dragon_ico_transformed.png")
                                   
            
                    message.set_audio(audio.Default, loop=False)
                    message.add_actions(label="Go to Website.", launch="https://github.com/Mester-Oxdan/Oxdan-Dragon-C")

                    message.show()

            asyncio.run(main())

    except Exception as e:
        print("Error:", e)
        msvcrt.getch()
    
update_program()