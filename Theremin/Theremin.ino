const int photoSensorPin = 0;
const int speakerPin = 8;
const int recordButtonPin = 12;
const int playbackButtonPin = 13;

const int photoSensorMinValue = 0;
const int photoSensorMaxValue = 1023;
const word speakerMinFrequency = 50;
const word speakerMaxFrequency = 4000;

const word singleToneTime = 20;
const word maxRecordTime = 5000;
const word recordMaxToneCount = maxRecordTime / singleToneTime;
word record[recordMaxToneCount+1] = {0};
word recordIndex = 0;

const short delayTime = 1000;

boolean isRecording = false;
boolean isPlayback = false;

void setup()
{
  pinMode(speakerPin, OUTPUT);
  pinMode(recordButtonPin, INPUT);
  pinMode(playbackButtonPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  short speakerFrequency = 0;
  
  if (!isRecording && HIGH == digitalRead(playbackButtonPin))
  {
    if (!isPlayback)
    {
      recordIndex = 0;
      isPlayback = true;
    }
    speakerFrequency = record[recordIndex++];
    
    if (0 == speakerFrequency) // end of record
    {
      recordIndex = 0; // loop record
      delay(delayTime); // wait delayTime before nex playback
    }  
  }
  else
  {
    isPlayback = false;
    
    const short photoSensorValue = analogRead(photoSensorPin);
    speakerFrequency = map(photoSensorValue, photoSensorMinValue, photoSensorMaxValue, 
                         speakerMinFrequency, speakerMaxFrequency); 
  }
  
  tone(speakerPin, speakerFrequency, singleToneTime);
  
  if (!isPlayback && HIGH == digitalRead(recordButtonPin))
  {
    if (!isRecording)
    {
      memset(record, 0, recordMaxToneCount+1);
      recordIndex = 0;
      isRecording = true;
    }
    record[(recordIndex++)%recordMaxToneCount] = speakerFrequency;
  }
  else
  {
    isRecording = false;
  }

  delay(10);
}

