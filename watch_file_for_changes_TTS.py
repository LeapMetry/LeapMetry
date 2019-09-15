import os, requests, time
from xml.etree import ElementTree
import vlc

from dotenv import load_dotenv
load_dotenv()

subscription_key = os.getenv("AZURE_SUBSCRIPTION_KEY")

class TextToSpeech(object):
    def __init__(self, subscription_key):
        print(f'LOG {time.strftime("%Y%m%d-%H%M")}: OBJECT INIT AT {time.time()}')
        self.subscription_key = subscription_key
        self.tts = ''
        self.timestr = time.strftime("%Y%m%d-%H%M")
        self.file_name = f'{self.tts.replace(" ", "_")}_{self.timestr}.mp3'
        self.last_access = 0
        self.access_token = None

    '''
    The TTS endpoint requires an access token. This method exchanges your
    subscription key for an access token that is valid for ten minutes.
    '''
    def get_token(self):
        fetch_token_url = "https://eastus.api.cognitive.microsoft.com/sts/v1.0/issueToken"
        headers = {
            'Ocp-Apim-Subscription-Key': self.subscription_key
        }
        response = requests.post(fetch_token_url, headers=headers)
        self.access_token = str(response.text)
        self.last_access = time.time()
        print(f'LOG {time.strftime("%Y%m%d-%H%M")}: New token acquired at {self.last_access}')

    def save_audio(self):
        if time.time() - self.last_access > 500:
            self.get_token()
        
        print(f'LOG {time.strftime("%Y%m%d-%H%M")}: Save Audio called with "{self.tts}"')
        self.file_name = f'{self.tts.replace(" ", "_")}_{self.timestr}.mp3'
        
        base_url = 'https://eastus.tts.speech.microsoft.com/'
        path = 'cognitiveservices/v1'
        constructed_url = base_url + path
        headers = {
            'Authorization': 'Bearer ' + self.access_token,
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': 'audio-16khz-32kbitrate-mono-mp3',
        }
        xml_body = ElementTree.Element('speak', version='1.0')
        xml_body.set('{http://www.w3.org/XML/1998/namespace}lang', 'en-us')
        voice = ElementTree.SubElement(xml_body, 'voice')
        voice.set('{http://www.w3.org/XML/1998/namespace}lang', 'en-US')
        voice.set('name', 'en-US-Guy24kRUS') # Short name for 'Microsoft Server Speech Text to Speech Voice (en-US, Guy24KRUS)'
        voice.text = self.tts
        body = ElementTree.tostring(xml_body)
        
        print(f'LOG {time.strftime("%Y%m%d-%H%M")}: Request sent at {time.time()}')
        response = requests.post(constructed_url, headers=headers, data=body)
        '''
        If a success response is returned, then the binary audio is written
        to file in your working directory. It is prefaced by sample and
        includes the date.
        '''
        if response.status_code == 200:
            with open(self.file_name, 'wb') as audio:
                audio.write(response.content)
            print(f'LOG {time.strftime("%Y%m%d-%H%M")}: File {self.file_name} played')
            p = vlc.MediaPlayer(self.file_name)
            try:
                p.play()
            except:
                p.play()
        else:
            print(f"\nLOG {time.strftime('%Y%m%d-%H%M')}: Status code: " + str(response.status_code) + "\nSomething went wrong. Check your subscription key and headers.\n")

if __name__ == "__main__":
    app = TextToSpeech(subscription_key)
    # app.get_token()
    mtime_last = 0
    pdata = []
    while True:
        mtime_cur = os.path.getmtime("texts.txt")
        if mtime_cur != mtime_last:
            time.sleep(1)
            print(f'LOG {time.strftime("%Y%m%d-%H%M")}: file watch event triggerred')
            with open('texts.txt', 'r') as file:
                data = file.read().split('\n')
                if data != pdata:
                    pdata = data
                    try:
                        app.tts = data[-1]
                        if len(data[-1]) > 0:
                            app.save_audio()
                    except:
                        print(f"LOG {time.strftime('%Y%m%d-%H%M')}: No data in file")
        mtime_last = mtime_cur








