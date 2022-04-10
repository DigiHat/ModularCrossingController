
#define LAPPROACHPIN_T1 A2
#define RAPPROACHPIN_T1 A1
#define LISLANDPIN_T1 A0
#define RISLANDPIN_T1 A3    

#define LAPPROACHPIN_T2 A4
#define RAPPROACHPIN_T2 A5
#define LISLANDPIN_T2 A6
#define RISLANDPIN_T2 A7

int lapp1, rapp1, lisl1, risl1;
int lapp2, rapp2, lisl2, risl2;

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  lapp1 = analogRead(LAPPROACHPIN_T1);
  rapp1 = analogRead(RAPPROACHPIN_T1);
  lisl1 = analogRead(LISLANDPIN_T1);
  risl1 = analogRead(RISLANDPIN_T1);

  lapp2 = analogRead(LAPPROACHPIN_T2);
  rapp2 = analogRead(RAPPROACHPIN_T2);
  lisl2 = analogRead(LISLANDPIN_T2);
  risl2 = analogRead(RISLANDPIN_T2);

  //Serial.print("Analog value: ");
  String str = "";
  String outString;
  outString = str + lapp1 + " " +  lisl1 + " " + risl1 + " " + rapp1 +" " + lapp2  + " " + lisl2 + " " + risl2+ " " + rapp2;
  Serial.println(outString);

  delay(250);

}
