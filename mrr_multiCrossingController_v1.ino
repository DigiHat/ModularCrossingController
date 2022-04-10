//Libraries
#include <SchedTask.h>


//Constants
#define APPROACH_TRIGGER_COOLDOWN 200    //time to turn off crossing if an approach is triggered but island is not occupied after x * 100ms (200 = 20 seconds)
#define ISLAND_EXIT_COOLDOWN 30          //time to turn off after x * 100ms (30 = 3 seconds)
#define DISABLE_COOLDOWN 70              //time approaches remain disabled after island cleared, (x * 100ms) + (ISLAND_EXIT_COOLDOWN * 100ms) (70 = 7s + 3s => 10s)
#define LIGHT_MODE 0                     //0=Common Anode, 1=Common Cathode
#define DETECT_THRESHOLD_ON 550          //AnalogInput below which crossing activates
#define DETECT_THRESHOLD_OFF 600         //AnalogInput above which crossing deactivates (Used for hysteresis)


//Global variables
  //Track 1
    //Pin Numbers (Need to be Analog inputs)
#define LAPPROACHPIN_T1 A2
#define RAPPROACHPIN_T1 A1
#define LISLANDPIN_T1 A0
#define RISLANDPIN_T1 A3
    //Analog Inputs
int lApproachIn_t1;
int rApproachIn_t1;
int lIslandIn_t1;
int rIslandIn_t1;
    //Activation_tracking
bool lAppActive_t1;
bool rAppActive_t1;
bool lIslActive_t1;
bool rIslActive_t1;
bool direction_t1;  //0=left, 1=right
bool lAppDisabled_t1;
bool rAppDisabled_t1;
int lAppTrigCooldown_t1;
int rAppTrigCooldown_t1;
int lAppDsblCooldown_t1;
int rAppDsblCooldown_t1;
int islandExitCooldown_t1;
bool active_t1;

  //Track 2
    //Pin Numbers (Need to be Analog inputs)
#define LAPPROACHPIN_T2 A4
#define RAPPROACHPIN_T2 A5
#define LISLANDPIN_T2 A6
#define RISLANDPIN_T2 A7
    //Analog Inputs
int lApproachIn_t2;
int rApproachIn_t2;
int lIslandIn_t2;
int rIslandIn_t2;
    //Activation_tracking
bool lAppActive_t2;
bool rAppActive_t2;
bool lIslActive_t2;
bool rIslActive_t2;
bool direction_t2;  //0=left, 1=right
bool lAppDisabled_t2;
bool rAppDisabled_t2;
int lAppTrigCooldown_t2;
int rAppTrigCooldown_t2;
int islandExitCooldown_t2;
bool active_t2;


/*
  //Track 3
    //Pin Numbers (Need to be Analog inputs)
#define LAPPROACHPIN_T3 A8
#define RAPPROACHPIN_T3 A9
#define LISLANDPIN_T3 A10
#define RISLANDPIN_T3 A11
    //Analog Inputs
int lApproachIn_t3;
int rApproachIn_t3;
int lIslandIn_t3;
int rIslandIn_t3;




  //Track 4
    //Pin Numbers (Need to be Analog inputs)
#define LAPPROACHPIN_T4 A12
#define RAPPROACHPIN_T4 A13
#define LISLANDPIN_T4 A14
#define RISLANDPIN_T4 A15
    //Analog Inputs
int lApproachIn_t4;
int rApproachIn_t4;
int lIslandIn_t4;
int rIslandIn_t4;




*/


  //Crossing 1
    //Pin Numbers (Digital pins)
#define LLIGHTPIN1_X1 52
#define LLIGHTPIN2_X1 51
#define RLIGHTPIN1_X1 50
#define RLIGHTPIN2_X1 53
    //Variables
bool active_x1; //0=off, 1=on
bool newActive_x1;  //0=Just started, 1=Already going
bool light_x1;  //0=left, 1=right
int lightCount_x1;

/*
  //Crossing 2
    //Pin Numbers (Digital pins)
#define LLIGHTPIN1_X2 #
#define LLIGHTPIN2_X2 #
#define RLIGHTPIN1_X2 #
#define RLIGHTPIN2_X2 #
    //Variables
bool active_x2; //0=off, 1=on
bool newActive_x2;  //0=Just started, 1=Already going
bool light_x2;  //0=left, 1=right
int lightCount_x2;

  //Crossing 3
    //Pin Numbers (Digital pins)
#define LLIGHTPIN1_X3 #
#define LLIGHTPIN2_X3 #
#define RLIGHTPIN1_X3 #
#define RLIGHTPIN2_X3 #
    //Variables
bool active_x3; //0=off, 1=on
bool newActive_x3;  //0=Just started, 1=Already going
bool light_x3;  //0=left, 1=right
int lightCount_x3;

  //Crossing 4
    //Pin Numbers (Digital pins)
#define LLIGHTPIN1_X4 #
#define LLIGHTPIN2_X4 #
#define RLIGHTPIN1_X4 #
#define RLIGHTPIN2_X4 #
    //Variables
bool active_x4; //0=off, 1=on
bool newActive_x4;  //0=Just started, 1=Already going
bool light_x4;  //0=left, 1=right
int lightCount_x4;
*/


//Function Prototypes
//------------------------------------------------------------------------------------------------------------------------------------------
void readInputs();
void determineTrackOccupancy();
void determineCrossingActivity();
void flash();

//Function Declarations
//------------------------------------------------------------------------------------------------------------------------------------------
SchedTask readTracks(0,100,readInputs);
SchedTask trackOccupancy(20,100,determineTrackOccupancy);
SchedTask crossingActivity(70,100,determineCrossingActivity);
SchedTask flasher(80,100,flash);


//Main Code
//------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  //Initialize Variables
    //Track 1
  lApproachIn_t1 = 900;
  rApproachIn_t1 = 900;
  lIslandIn_t1 = 900;
  rIslandIn_t1 = 900;

  lAppActive_t1 = 0;
  rAppActive_t1 = 0;
  lIslActive_t1 = 0;
  rIslActive_t1 = 0;
  
  direction_t1 = 0;  //0=left, 1=right
  lAppDisabled_t1 = false;
  rAppDisabled_t1 = false;
  
  lAppTrigCooldown_t1 = APPROACH_TRIGGER_COOLDOWN;
  rAppTrigCooldown_t1 = APPROACH_TRIGGER_COOLDOWN;
  lAppDsblCooldown_t1 = DISABLE_COOLDOWN;
  rAppDsblCooldown_t1 = DISABLE_COOLDOWN;
  islandExitCooldown_t1 = 0;
  
  active_t1 = 0;

  
    //Track 2

/*
    //Track 3

    //Track 4

*/
    //X-ing 1
  pinMode(LLIGHTPIN1_X1, OUTPUT);
  pinMode(LLIGHTPIN2_X1, OUTPUT);
  pinMode(RLIGHTPIN1_X1, OUTPUT);
  pinMode(RLIGHTPIN2_X1, OUTPUT);
  if(LIGHT_MODE == 0)
  {
    digitalWrite(LLIGHTPIN1_X1, HIGH);
    digitalWrite(LLIGHTPIN2_X1, HIGH);
    digitalWrite(RLIGHTPIN1_X1, HIGH);
    digitalWrite(RLIGHTPIN2_X1, HIGH);
  }
  active_x1 = 0; //0=off, 1=on
  newActive_x1 = 1;
  light_x1 = 0;
  lightCount_x1 = -1;
/*
    //X-ing 2
  pinMode(LLIGHTPIN1_X2, OUTPUT);
  pinMode(LLIGHTPIN2_X2, OUTPUT);
  pinMode(RLIGHTPIN1_X2, OUTPUT);
  pinMode(RLIGHTPIN2_X2, OUTPUT);
  active_x2 = 0; //0=off, 1=on
  newActive_x2 = 1;
  light_x2 = 0;
  lightCount_x2 = 0;
  
    //X-ing 3
  pinMode(LLIGHTPIN1_X3, OUTPUT);
  pinMode(LLIGHTPIN2_X3, OUTPUT);
  pinMode(RLIGHTPIN1_X3, OUTPUT);
  pinMode(RLIGHTPIN2_X3, OUTPUT);
  active_x3 = 0; //0=off, 1=on
  newActive_x3 = 1;
  light_x3 = 0;
  lightCount_x3 = 0;
  
    //X-ing 4
  pinMode(LLIGHTPIN1_X4, OUTPUT);
  pinMode(LLIGHTPIN2_X4, OUTPUT);
  pinMode(RLIGHTPIN1_X4, OUTPUT);
  pinMode(RLIGHTPIN2_X4, OUTPUT);
  active_x4 = 0; //0=off, 1=on
  newActive_x4 = 1;
  light_x4 = 0;
  lightCount_x4 = 0;
*/

  Serial.begin(9600);

} //End setup()

void loop() {
  SchedBase::dispatcher();
} //End loop()

//Functions
//------------------------------------------------------------------------------------------------------------------------------------------
void readInputs() //Reads analog values from track photocells
{
  //Track 1
  lApproachIn_t1 = analogRead(LAPPROACHPIN_T1);
  rApproachIn_t1 = analogRead(RAPPROACHPIN_T1);
  lIslandIn_t1 = analogRead(LISLANDPIN_T1);
  rIslandIn_t1 = analogRead(RISLANDPIN_T1);

    //Process Input
  if((lAppActive_t1 == true) && (lApproachIn_t1 > DETECT_THRESHOLD_OFF))
  {
    lAppActive_t1 = false;
  } else if((lAppActive_t1 == false) && (lApproachIn_t1 < DETECT_THRESHOLD_ON))
  {
    lAppActive_t1 = true;
  }
  
  if((rAppActive_t1 == true) && (rApproachIn_t1 > DETECT_THRESHOLD_OFF))
  {
    rAppActive_t1 = false;
  } else if((rAppActive_t1 == false) && (rApproachIn_t1 < DETECT_THRESHOLD_ON))
  {
    rAppActive_t1 = true;
  }

  if((lIslActive_t1 == true) && (lIslandIn_t1 > DETECT_THRESHOLD_OFF))
  {
    lIslActive_t1 = false;
    
  } else if((lIslActive_t1 == false) && (lIslandIn_t1 < DETECT_THRESHOLD_ON))
  {
    lIslActive_t1 = true;
  }

    if((rIslActive_t1 == true) && (rIslandIn_t1 > DETECT_THRESHOLD_OFF))
  {
    rIslActive_t1 = false;
    
  } else if((rIslActive_t1 == false) && (rIslandIn_t1 < DETECT_THRESHOLD_ON))
  {
    rIslActive_t1 = true;
  }

/*
  //Track 2
  lApproachIn_t2 = analogRead(LAPPROACHPIN_T2);
  rApproachIn_t2 = analogRead(RAPPROACHPIN_T2);
  lIslandIn_t2 = analogRead(LISLANDPIN_T2);
  rIslandIn_t2 = analogRead(RISLANDPIN_T2);

    //Process Input
  if((lAppActive_t2 == true) && (lApproachIn_t2 > DETECT_THRESHOLD_OFF))
  {
    lAppActive_t2 = false;
  } else if((lAppActive_t2 == false) && (lApproachIn_t2 < DETECT_THRESHOLD_ON))
  {
    lAppActive_t2 = true;
  }
  
  if((rAppActive_t2 == true) && (rApproachIn_t2 > DETECT_THRESHOLD_OFF))
  {
    rAppActive_t2 = false;
  } else if((rAppActive_t2 == false) && (rApproachIn_t2 < DETECT_THRESHOLD_ON))
  {
    rAppActive_t2 = true;
  }

  if((lIslActive_t2 == true) && (lIslandIn_t2 > DETECT_THRESHOLD_OFF))
  {
    lIslActive_t2 = false;
    
  } else if((lIslActive_t2 == false) && (lIslandIn_t2 < DETECT_THRESHOLD_ON))
  {
    lIslActive_t2 = true;
  }

    if((rIslActive_t2 == true) && (rIslandIn_t2 > DETECT_THRESHOLD_OFF))
  {
    rIslActive_t2 = false;
    
  } else if((rIslActive_t2 == false) && (rIslandIn_t2 < DETECT_THRESHOLD_ON))
  {
    rIslActive_t2 = true;
  }
  */

/*
  //Track 3
  lApproachIn_t3 = analogRead(LAPPROACHPIN_T3);
  rApproachIn_t3 = analogRead(RAPPROACHPIN_T3);
  lIslandIn_t3 = analogRead(LISLANDPIN_T3);
  rIslandIn_t3 = analogRead(RISLANDPIN_T3);

  //Track 4
  lApproachIn_t4 = analogRead(LAPPROACHPIN_T4);
  rApproachIn_t4 = analogRead(RAPPROACHPIN_T4);
  lIslandIn_t4 = analogRead(LISLANDPIN_T4);
  rIslandIn_t4 = analogRead(RISLANDPIN_T4);
*/

  return;
} //End readTracks()


//======================================================================
void determineTrackOccupancy() //Decides if tracks, runs every 100ms
{

    /*Activation_tracking
bool lAppActive_t1;
bool rAppActive_t1;
bool lIslActive_t1;
bool rIslActive_t1;
bool direction_t1;  //0=left, 1=right
bool lAppDisabled;
bool rAppDisabled;
int lAppTrigCooldown_t1;
int rAppTrigCooldown_t1;
int lAppDsblCooldown_t1;
int rAppDsblCooldown_t1;
int islandExitCooldown_t1;
bool active_t1;*/

  if(active_t1 == 0) //Track inactive--------------------------------------------------------------------------------------------------------
  {

    //Do disabled track things
    if(lAppDisabled_t1 == 1)
    {
      if(lAppDsblCooldown_t1 < DISABLE_COOLDOWN)
      {
        lAppDsblCooldown_t1++;
      }

      if((lAppDsblCooldown_t1 >= DISABLE_COOLDOWN) && (lAppActive_t1 == 0))
      {
        lAppDisabled_t1 = 0;
      }
    }
    if(rAppDisabled_t1 == 1)
    {
      if(rAppDsblCooldown_t1 < DISABLE_COOLDOWN)
      {
        rAppDsblCooldown_t1++;
      }

      if((rAppDsblCooldown_t1 >= DISABLE_COOLDOWN) && (rAppActive_t1 == 0))
      {
        rAppDisabled_t1 = 0;
      }
    }

     //Activate track if appropriate
    if(((lAppActive_t1 == 1) && (lAppDisabled_t1 == 0)) || (lIslActive_t1 == 1) || (rIslActive_t1 == 1) || ((rAppActive_t1 == 1) && (rAppDisabled_t1 == 0)))
    {
      active_t1 = 1;

      if((lAppActive_t1 == 1) && (lAppDisabled_t1 == 0))
      {
        lAppTrigCooldown_t1 = 0;
      }
      if((rAppActive_t1 == 1) && (rAppDisabled_t1 == 0))
      {
        rAppTrigCooldown_t1 = 0;
      }
      if((lIslActive_t1 == 1) || (rIslActive_t1 == 1))
      {
        islandExitCooldown_t1 = 0;

        //Set direction
        if((lIslActive_t1 == 0) && (rIslActive_t1 == 1))
        {
          direction_t1 = 1;
        } else if((lIslActive_t1 == 1) && (rIslActive_t1 == 0))
        {
          direction_t1 = 0;
        }
      }
    }

    
  } else {  //Track active-----------------------------------------------------------------------------------------------------------------

    //Approach Handling
    if(((lAppTrigCooldown_t1 < APPROACH_TRIGGER_COOLDOWN) || (rAppTrigCooldown_t1 < APPROACH_TRIGGER_COOLDOWN)) && ((lIslActive_t1 == 0) || (rIslActive_t1 == 0)))
    {
      if(lAppTrigCooldown_t1 < APPROACH_TRIGGER_COOLDOWN)
      {
        lAppTrigCooldown_t1++;

        if(lAppTrigCooldown_t1 >= APPROACH_TRIGGER_COOLDOWN)
        {
          lAppDisabled_t1 = 1;
        }
      }

      if(rAppTrigCooldown_t1 < APPROACH_TRIGGER_COOLDOWN)
      {
        rAppTrigCooldown_t1++;

        if(rAppTrigCooldown_t1 >= APPROACH_TRIGGER_COOLDOWN)
        {
          rAppDisabled_t1 = 1;
        }
      }
    }


    //Island handling
    if((lIslActive_t1 == 1) || (rIslActive_t1 == 1))
    {
      islandExitCooldown_t1 = 0;

      lAppDisabled_t1 = 0;
      rAppDisabled_t1 = 0;
      lAppTrigCooldown_t1 = APPROACH_TRIGGER_COOLDOWN;
      rAppTrigCooldown_t1 = APPROACH_TRIGGER_COOLDOWN;
      lAppDsblCooldown_t1 = DISABLE_COOLDOWN;
      rAppDsblCooldown_t1 = DISABLE_COOLDOWN;
      

      //Recalibrate direction
      if((lIslActive_t1 == 0) && (rIslActive_t1 == 1))
      {
        direction_t1 =1 ;
      } else if ((lIslActive_t1 == 1) && (rIslActive_t1 == 0))
      {
        direction_t1 = 0;
      }
      
    } else if(islandExitCooldown_t1 < ISLAND_EXIT_COOLDOWN)
    {
      islandExitCooldown_t1++;
    }


    //Deactivate if appropriate
    if(((lAppActive_t1 == 0) || (lAppDisabled_t1 == 1)) && ((lIslActive_t1 == 0) && (rIslActive_t1 == 0) && (islandExitCooldown_t1 < ISLAND_EXIT_COOLDOWN)) && ((rAppActive_t1 == 0) || (rAppDisabled_t1 == 1)))
    {
      active_t1 = 0;

      if((lAppDisabled_t1 == 0) && (rAppDisabled_t1 == 0))
      {
        if(direction_t1 == 0)
        {
          lAppDisabled_t1 = 1;
          lAppDsblCooldown_t1 = 0;
        } else 
        {
          rAppDisabled_t1 = 1;
          rAppDsblCooldown_t1 = 0;
        }
      }
    }
    
  }

  
   /* //Determine track Activity
  if(active_t1 == false) //Activation Conditions
  {
    if((lAppActive_t1 == 1) && (lAppDisabled_t1 == false)) //Approach Left activation
    {
      active_t1 = true;
      direction_t1 = 1;     //Traveling right
      lAppTrigCooldown_t1 = 0; //Start cooldown
    } else if ((rAppActive_t1 == 1) && (rAppDisabled_t1 == false)) //Approach Right activation
    {
      active_t1 == true;
      direction_t1 = 0; //Traveling left
      rAppTrigCooldown_t1 = 0; //Start cooldown
    } else if (lIslActive_t1 == 1)
    {
      active_t1 = true;
      direction_t1 = 1; //Traveling right
      islandExitCooldown_t1 = 0; //Start cooldown
    } else if (rIslActive_t1 == 1)
    {
      active_t1 = true;
      direction_t1 = 0; //Traveling left
      islandExitCooldown_t1 = 0; //Start cooldown

      
    } else {  //Crossing Unactivated

      //Approaches are disabled, handle cooldown timers
      if(lAppDisabled_t1 == true)
      {
        if(lAppDsblCooldown_t1 < DISABLE_COOLDOWN)
        {
          //Do nuthin'
        } else if(lAppTrigCooldown_t1 < APPROACH_TRIGGER_COOLDOWN)
        {
          lAppTrigCooldown_t1++;
        } else if (lAppActive_t1 == 1)
        {
          //Do nothing, do not reset cooldown until train clears sensor
        } else {
          lAppDisabled_t1 = false;
        }
      }

      if(rAppDisabled_t1 == true)
      {
        if(rAppDsblCooldown_t1 < DISABLE_COOLDOWN)
        {
          //do nuthin'
        } else if(rAppTrigCooldown_t1 < APPROACH_TRIGGER_COOLDOWN)
        {
          rAppTrigCooldown_t1++;
        } else if (rAppActive_t1 == 1)
        {
          //Do nothing, do not reset cooldown until train clears sensor
        } else {
          rAppDisabled_t1 = false;
        }
      }
    }

      
  } else { //Crossing is already active
      //Handle approach cooldowns
    //Counts down Approach activations
    if((lIslActive_t1 == 0) && (rIslActive_t1 == 0) && (islandExitCooldown_t1 >= ISLAND_EXIT_COOLDOWN))
    {
      if((lAppTrigCooldown_t1 >= APPROACH_TRIGGER_COOLDOWN) && (rAppTrigCooldown_t1 >= APPROACH_TRIGGER_COOLDOWN))
      {
        //Do nuthin'
      } else {
        if(lAppTrigCooldown_t1 < APPROACH_TRIGGER_COOLDOWN)
        {
          lAppTrigCooldown_t1++;
        }

        if(rAppTrigCooldown_t1 < APPROACH_TRIGGER_COOLDOWN)
        {
          rAppTrigCooldown_t1++;
        }

        if((lAppTrigCooldown_t1 >= APPROACH_TRIGGER_COOLDOWN) && (rAppTrigCooldown_t1 >= APPROACH_TRIGGER_COOLDOWN))
        {
          active_t1 = 0;
        }
      }
    }

    //Island direction correction
    if((lIslActive_t1 == 1) && (rIslActive_t1 == 0))
    {
      direction_t1 = 0;
    } else if((lIslActive_t1 == 0) && (rIslActive_t1 == 1))
    {
      direction_t1 = 1;
    }

    //Reset Island cooldown
    if((lIslActive_t1 == 1) || (rIslActive_t1 == 1))
    {
      islandExitCooldown_t1 = 0;                       //Reset Island cooldown
      lAppTrigCooldown_t1 = APPROACH_TRIGGER_COOLDOWN; //Get rid of original approach cooldowns
      rAppTrigCooldown_t1 = APPROACH_TRIGGER_COOLDOWN;
      lAppDsblCooldown_t1 = DISABLE_COOLDOWN;          //Get rid of any residual disabled
      rAppDsblCooldown_t1 = DISABLE_COOLDOWN;
      lAppDisabled_t1 = 0;
      rAppDisabled_t1 = 0;
      
    } else if((lIslActive_t1 == 0) && (rIslActive_t1 == 0))
    {
      if(islandExitCooldown_t1 < ISLAND_EXIT_COOLDOWN)
      {
        islandExitCooldown_t1++;
      } else {
        active_t1 = false;
        if(direction_t1 == 0)
        {
          lAppDisabled_t1 = 1;
          lAppDsblCooldown_t1 = 0;

        } else {
          rAppDisabled_t1 = 1;
          rAppDsblCooldown_t1 = 0;
        }
      }
    }
    
    





    
  }
  
    //Handles Cooldown for Island Disable
  if((lAppDisabled_t1 == 1) && (lAppTrigCooldown_t1 >= APPROACH_TRIGGER_COOLDOWN))
  {
    if(lAppDsblCooldown_t1 < DISABLE_COOLDOWN)
    {
      lAppDsblCooldown_t1++;
      
    } else {
      if(lAppActive_t1 == 1)
      {
        //do nuthin' until train clears
      } else {
        lAppDisabled_t1 = 0;
      }
    }
  }
  
  if((rAppDisabled_t1 == 1) && (rAppTrigCooldown_t1 >= APPROACH_TRIGGER_COOLDOWN))
  {
    if(rAppDsblCooldown_t1 < DISABLE_COOLDOWN)
    {
      rAppDsblCooldown_t1++;
    } else {
      if(rAppActive_t1 == 1)
      {
        //do nuthin' until train clears
      } else {
        rAppDisabled_t1 = 0;
      }
    }
  }*/

  //DEBUG
  //active_t1 = 1;
  String strout = "";
  String strOut = strout + active_t1;
  Serial.println(strOut);

  //Track 2


/*
  //Track 3


  //Track 4

*/
  return;
} //End determineTrackOccupancy()


//======================================================================
void determineCrossingActivity()  //Decides which crossings should be active, runs every 100ms
{
  //X-ing 1
  if(active_t1 /*|| active_t2*/)
  {
    active_x1 = true;
  } else {
    active_x1 = false;
  }

/*
  //X-ing 2
  if(active_t#)
  {
    active_x2 = 1;
  } else {
    active_x2 = 0;
  }

  //X-ing 3
  if(active_t#)
  {
    active_x3 = 1;
  } else {
    active_x3 = 0;
  }

  //X-ing 4
  if(active_t4)
  {
    active_x4 = 1;
  } else {
    active_x4 = 0;
  }
*/



} //End determineCrossingActivity

//======================================================================
void flash()  //Flashes crossing lights, runs every 100ms
{
  //X-ing 1
  if((active_x1 == true) && (light_x1 == 0) && (lightCount_x1 == 0) && (newActive_x1 == true))
  {
    newActive_x1 = false;
    if(LIGHT_MODE == 0) //Common Anode
    {
      digitalWrite(LLIGHTPIN1_X1, LOW);
      digitalWrite(LLIGHTPIN2_X1, LOW);
      digitalWrite(RLIGHTPIN1_X1, HIGH);
      digitalWrite(RLIGHTPIN2_X1, HIGH);
    } else {            //Common Cathode
      digitalWrite(LLIGHTPIN1_X1, HIGH);
      digitalWrite(LLIGHTPIN2_X1, HIGH);
      digitalWrite(RLIGHTPIN1_X1, LOW);
      digitalWrite(RLIGHTPIN2_X1, LOW);
    }
    
  }





  
  if((active_x1 == 0) && (light_x1 == 0) && (lightCount_x1 < 0) && (newActive_x1 == true)) //Crossing is not active and stays inactive
  {
    //Do nuthin'
    
  } else if((active_x1 == 0) && (light_x1 == 0) && (lightCount_x1 == 0) && (newActive_x1 == false)) //Crossing Deactivates
  {
    if(LIGHT_MODE == 0) //Common Anode
    {
      digitalWrite(LLIGHTPIN1_X1, HIGH);
      digitalWrite(LLIGHTPIN2_X1, HIGH);
      digitalWrite(RLIGHTPIN1_X1, HIGH);
      digitalWrite(RLIGHTPIN2_X1, HIGH);
    } else {            //Common Cathode
      digitalWrite(LLIGHTPIN1_X1, LOW);
      digitalWrite(LLIGHTPIN2_X1, LOW);
      digitalWrite(RLIGHTPIN1_X1, LOW);
      digitalWrite(RLIGHTPIN2_X1, LOW);
    }
    newActive_x1 = true;
    lightCount_x1 = -1;
    
  } else if((active_x1 == 1) && (light_x1 == 0) && (lightCount_x1 < 0) && (newActive_x1 == true)) //Crossing Activates
  {
    if(LIGHT_MODE == 0) //Common Anode
    {
      digitalWrite(LLIGHTPIN1_X1, LOW);
      digitalWrite(LLIGHTPIN2_X1, LOW);
      digitalWrite(RLIGHTPIN1_X1, HIGH);
      digitalWrite(RLIGHTPIN2_X1, HIGH);
    } else {            //Common Cathode
      digitalWrite(LLIGHTPIN1_X1, HIGH);
      digitalWrite(LLIGHTPIN2_X1, HIGH);
      digitalWrite(RLIGHTPIN1_X1, LOW);
      digitalWrite(RLIGHTPIN2_X1, LOW);
    }
    newActive_x1 = false;
    lightCount_x1++;
    
  } else if(lightCount_x1 >= 5)  //Time to alternate lights
  {
    if (light_x1 == 0)
    {
      if(LIGHT_MODE == 0) //Common Anode
      {
        digitalWrite(LLIGHTPIN1_X1, HIGH);
        digitalWrite(LLIGHTPIN2_X1, HIGH);
        digitalWrite(RLIGHTPIN1_X1, LOW);
        digitalWrite(RLIGHTPIN2_X1, LOW);
      } else {            //Common Cathode
        digitalWrite(LLIGHTPIN1_X1, LOW);
        digitalWrite(LLIGHTPIN2_X1, LOW);
        digitalWrite(RLIGHTPIN1_X1, HIGH);
        digitalWrite(RLIGHTPIN2_X1, HIGH);
      }
    } else {
      if(LIGHT_MODE == 0) //Common Anode
      {
        digitalWrite(LLIGHTPIN1_X1, LOW);
        digitalWrite(LLIGHTPIN2_X1, LOW);
        digitalWrite(RLIGHTPIN1_X1, HIGH);
        digitalWrite(RLIGHTPIN2_X1, HIGH);
      } else {            //Common Cathode
        digitalWrite(LLIGHTPIN1_X1, HIGH);
        digitalWrite(LLIGHTPIN2_X1, HIGH);
        digitalWrite(RLIGHTPIN1_X1, LOW);
        digitalWrite(RLIGHTPIN2_X1, LOW);
      } 
    }
    light_x1 = !light_x1;
    lightCount_x1 = 0;
    
  } else //Crossing is Active but it's not time to alternate lights
  {
    lightCount_x1++;
    newActive_x1 = false;

    
    
  }

/*  
  //X-ing 2
  if((active_x2 == 0) && (light_x2 == 0) && (lightCount_x2 == 0) && (newActive_x2 == true)) //Crossing is not active and stays inactive
  {
    //Do nuthin'
    
  } else if((active_x2 == 0) && (light_x2 == 0) && (lightCount_x2 == 0) && (newActive_x2 == false)) //Crossing Deactivates
  {
    if(LIGHT_MODE == 0) //Common Anode
    {
      digitalWrite(LLIGHTPIN1_X2, HIGH);
      digitalWrite(LLIGHTPIN2_X2, HIGH);
      digitalWrite(RLIGHTPIN1_X2, HIGH);
      digitalWrite(RLIGHTPIN2_X2, HIGH);
    } else {            //Common Cathode
      digitalWrite(LLIGHTPIN1_X2, LOW);
      digitalWrite(LLIGHTPIN2_X2, LOW);
      digitalWrite(RLIGHTPIN1_X2, LOW);
      digitalWrite(RLIGHTPIN2_X2, LOW);
    }
    newActive_x2 = true;
    
  } else if((active_x2 == 1) && (light_x2 == 0) && (lightCount_x2 == 0) && (newActive_x2 == true)) //Crossing Activates
  {
    if(LIGHT_MODE == 0) //Common Anode
    {
      digitalWrite(LLIGHTPIN1_X2, LOW);
      digitalWrite(LLIGHTPIN2_X2, LOW);
      digitalWrite(RLIGHTPIN1_X2, HIGH);
      digitalWrite(RLIGHTPIN2_X2, HIGH);
    } else {            //Common Cathode
      digitalWrite(LLIGHTPIN1_X2, HIGH);
      digitalWrite(LLIGHTPIN2_X2, HIGH);
      digitalWrite(RLIGHTPIN1_X2, LOW);
      digitalWrite(RLIGHTPIN2_X2, LOW);
    }
    newActive_x2 = false;
    
  } else if(lightCount_x2 < 5)  //Crossing is Active but it's not time to alternate lights
  {
    lightCount_x2++;
    
  } else if(lightCount_x2 >= 5) //Time to alternate lights
  {
    if (light_x2 == 0)
    {
      if(LIGHT_MODE == 0) //Common Anode
      {
        digitalWrite(LLIGHTPIN1_X2, HIGH);
        digitalWrite(LLIGHTPIN2_X2, HIGH);
        digitalWrite(RLIGHTPIN1_X2, LOW);
        digitalWrite(RLIGHTPIN2_X2, LOW);
      } else {            //Common Cathode
        digitalWrite(LLIGHTPIN1_X2, LOW);
        digitalWrite(LLIGHTPIN2_X2, LOW);
        digitalWrite(RLIGHTPIN1_X2, HIGH);
        digitalWrite(RLIGHTPIN2_X2, HIGH);
      }
    } else {
      if(LIGHT_MODE == 0) //Common Anode
      {
        digitalWrite(LLIGHTPIN1_X2, LOW);
        digitalWrite(LLIGHTPIN2_X2, LOW);
        digitalWrite(RLIGHTPIN1_X2, HIGH);
        digitalWrite(RLIGHTPIN2_X2, HIGH);
      } else {            //Common Cathode
        digitalWrite(LLIGHTPIN1_X2, HIGH);
        digitalWrite(LLIGHTPIN2_X2, HIGH);
        digitalWrite(RLIGHTPIN1_X2, LOW);
        digitalWrite(RLIGHTPIN2_X2, LOW);
      } 
    }
    light_x2 = !light_x2;
    lightCount_x2 = 0;
  }
  
  //X-ing 3
if((active_x3 == 0) && (light_x3 == 0) && (lightCount_x3 == 0) && (newActive_x3 == true)) //Crossing is not active and stays inactive
  {
    //Do nuthin'
    
  } else if((active_x3 == 0) && (light_x3 == 0) && (lightCount_x3 == 0) && (newActive_x3 == false)) //Crossing Deactivates
  {
    if(LIGHT_MODE == 0) //Common Anode
    {
      digitalWrite(LLIGHTPIN1_X3, HIGH);
      digitalWrite(LLIGHTPIN2_X3, HIGH);
      digitalWrite(RLIGHTPIN1_X3, HIGH);
      digitalWrite(RLIGHTPIN2_X3, HIGH);
    } else {            //Common Cathode
      digitalWrite(LLIGHTPIN1_X3, LOW);
      digitalWrite(LLIGHTPIN2_X3, LOW);
      digitalWrite(RLIGHTPIN1_X3, LOW);
      digitalWrite(RLIGHTPIN2_X3, LOW);
    }
    newActive_x3 = true;
    
  } else if((active_x3 == 1) && (light_x3 == 0) && (lightCount_x3 == 0) && (newActive_x3 == true)) //Crossing Activates
  {
    if(LIGHT_MODE == 0) //Common Anode
    {
      digitalWrite(LLIGHTPIN1_X3, LOW);
      digitalWrite(LLIGHTPIN2_X3, LOW);
      digitalWrite(RLIGHTPIN1_X3, HIGH);
      digitalWrite(RLIGHTPIN2_X3, HIGH);
    } else {            //Common Cathode
      digitalWrite(LLIGHTPIN1_X3, HIGH);
      digitalWrite(LLIGHTPIN2_X3, HIGH);
      digitalWrite(RLIGHTPIN1_X3, LOW);
      digitalWrite(RLIGHTPIN2_X3, LOW);
    }
    newActive_x3 = false;
    
  } else if(lightCount_x3 < 5)  //Crossing is Active but it's not time to alternate lights
  {
    lightCount_x3++;
    
  } else if(lightCount_x3 >= 5) //Time to alternate lights
  {
    if (light_x3 == 0)
    {
      if(LIGHT_MODE == 0) //Common Anode
      {
        digitalWrite(LLIGHTPIN1_X3, HIGH);
        digitalWrite(LLIGHTPIN2_X3, HIGH);
        digitalWrite(RLIGHTPIN1_X3, LOW);
        digitalWrite(RLIGHTPIN2_X3, LOW);
      } else {            //Common Cathode
        digitalWrite(LLIGHTPIN1_X3, LOW);
        digitalWrite(LLIGHTPIN2_X3, LOW);
        digitalWrite(RLIGHTPIN1_X3, HIGH);
        digitalWrite(RLIGHTPIN2_X3, HIGH);
      }
    } else {
      if(LIGHT_MODE == 0) //Common Anode
      {
        digitalWrite(LLIGHTPIN1_X3, LOW);
        digitalWrite(LLIGHTPIN2_X3, LOW);
        digitalWrite(RLIGHTPIN1_X3, HIGH);
        digitalWrite(RLIGHTPIN2_X3, HIGH);
      } else {            //Common Cathode
        digitalWrite(LLIGHTPIN1_X3, HIGH);
        digitalWrite(LLIGHTPIN2_X3, HIGH);
        digitalWrite(RLIGHTPIN1_X3, LOW);
        digitalWrite(RLIGHTPIN2_X3, LOW);
      } 
    }
    light_x3 = !light_x3;
    lightCount_x3 = 0;
  }

  //X-ing 4
  if((active_x4 == 0) && (light_x4 == 0) && (lightCount_x4 == 0) && (newActive_x4 == true)) //Crossing is not active and stays inactive
  {
    //Do nuthin'
    
  } else if((active_x4 == 0) && (light_x4 == 0) && (lightCount_x4 == 0) && (newActive_x4 == false)) //Crossing Deactivates
  {
    if(LIGHT_MODE == 0) //Common Anode
    {
      digitalWrite(LLIGHTPIN1_X4, HIGH);
      digitalWrite(LLIGHTPIN2_X4, HIGH);
      digitalWrite(RLIGHTPIN1_X4, HIGH);
      digitalWrite(RLIGHTPIN2_X4, HIGH);
    } else {            //Common Cathode
      digitalWrite(LLIGHTPIN1_X4, LOW);
      digitalWrite(LLIGHTPIN2_X4, LOW);
      digitalWrite(RLIGHTPIN1_X4, LOW);
      digitalWrite(RLIGHTPIN2_X4, LOW);
    }
    newActive_x4 = true;
    
  } else if((active_x4 == 1) && (light_x4 == 0) && (lightCount_x4 == 0) && (newActive_x4 == true)) //Crossing Activates
  {
    if(LIGHT_MODE == 0) //Common Anode
    {
      digitalWrite(LLIGHTPIN1_X4, LOW);
      digitalWrite(LLIGHTPIN2_X4, LOW);
      digitalWrite(RLIGHTPIN1_X4, HIGH);
      digitalWrite(RLIGHTPIN2_X4, HIGH);
    } else {            //Common Cathode
      digitalWrite(LLIGHTPIN1_X4, HIGH);
      digitalWrite(LLIGHTPIN2_X4, HIGH);
      digitalWrite(RLIGHTPIN1_X4, LOW);
      digitalWrite(RLIGHTPIN2_X4, LOW);
    }
    newActive_x4 = false;
    
  } else if(lightCount_x4 < 5)  //Crossing is Active but it's not time to alternate lights
  {
    lightCount_x4++;
    
  } else if(lightCount_x4 >= 5) //Time to alternate lights
  {
    if (light_x4 == 0)
    {
      if(LIGHT_MODE == 0) //Common Anode
      {
        digitalWrite(LLIGHTPIN1_X4, HIGH);
        digitalWrite(LLIGHTPIN2_X4, HIGH);
        digitalWrite(RLIGHTPIN1_X4, LOW);
        digitalWrite(RLIGHTPIN2_X4, LOW);
      } else {            //Common Cathode
        digitalWrite(LLIGHTPIN1_X4, LOW);
        digitalWrite(LLIGHTPIN2_X4, LOW);
        digitalWrite(RLIGHTPIN1_X4, HIGH);
        digitalWrite(RLIGHTPIN2_X4, HIGH);
      }
    } else {
      if(LIGHT_MODE == 0) //Common Anode
      {
        digitalWrite(LLIGHTPIN1_X4, LOW);
        digitalWrite(LLIGHTPIN2_X4, LOW);
        digitalWrite(RLIGHTPIN1_X4, HIGH);
        digitalWrite(RLIGHTPIN2_X4, HIGH);
      } else {            //Common Cathode
        digitalWrite(LLIGHTPIN1_X4, HIGH);
        digitalWrite(LLIGHTPIN2_X4, HIGH);
        digitalWrite(RLIGHTPIN1_X4, LOW);
        digitalWrite(RLIGHTPIN2_X4, LOW);
      } 
    }
    light_x4 = !light_x4;
    lightCount_x4 = 0;
  }
*/  


//POOTIS
  return;
} //End flash()
