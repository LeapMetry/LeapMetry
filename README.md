# LeapMetry

## Built by

ECE's best: Aditya Arora [@arora-aditya] + Rosemary Wang [@RosemaryW] + Yousuf Hali [@yousufhali]

## Inspiration

National Institute on Deafness and Other Communication Disorders (NIDCD) estimates that at least 6 to 8 million people in the North America suffer from some form of speech impediment. We set out to solve this problem by building a project that would allow those people to use their hands, and gestures, to convey phrases.

## What it does

Our project detects the hand gestures of the speech impaired person, and translates them to phrases which is fed to a google home for the listener to listen to.


## How does it work? 
Our project utilizes a Leap Motion hand sensor to detect the hands, and fingers that the people are displaying in front of the sensor, and translates them to phrases and characters, much like the American Sign Language. It then feeds those sentences to a Google Home where it can then be output for the listener to hear and respond to!
​
## Challenges we ran into
The Leap Motion sensor, despite being in production for a long while, has extremely poor installation instructions. Multiple errors in the installation stage, plagued the start of our project. At one point we were using a JS script which was not being served by their CDN anymore, and was instead extracted by us using the Wayback Machine (Internet Archive). 
​​
## Accomplishments that we're proud of
Getting over the hurdle of the Leap Motion Sensor, and finally getting to interact with the sensor was the most rewarding feeling ever!
​
## What we Learned
The Leap Motion sensor is a super cool device, especially at the price point it is being sold at. Moreover, given more time we could definitely see ourselves train our model to identify American Sign Language, especially since the sensor does one level of hand and palm extraction using its sensors itself!

We also learned the usage of the text-to-speech API provided by Microsoft Azure to relay the voice back to the user!

## What's next
The obvious next steps for our project is to extract the American Sign Language, and figure out a way to embed more and more regional gestures as is common with communities of people with speech impediments!
​
## Built With

- Azure Cognitive Services - Text-To-Speech
- Leap Motion
- C++
- Python
- JavaScript
​
