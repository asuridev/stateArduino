#define _ledR 10
#define _ledY 9
#define _ledG 8
#define _button 3
#include <AsButton.h>
#include <AsTime.h>
#include <AsLed.h>

AsLed ledR(_ledR, ACTIVE_HIGH);
AsLed ledY(_ledY, ACTIVE_HIGH);
AsLed ledG(_ledG, ACTIVE_HIGH);
AsTime timer;
AsButton button(_button);
enum modelMode {
   working,
   standby
 };

enum modelLight {
   red,
   redYellow,
   green,
   yellow,
   end
 };
 
struct modelState {
  modelMode mode;
  modelLight light;
  byte timing[4]= {3,1,2,1};// tiempos en segundos R,RY,G,Y
  byte crono;
  };
  
modelState state; // creo la variable estado
  
modelState setDefault(){
  modelState obj;
  //define los valores por defecto del state
  obj.mode = working;
  obj.light = red;
  obj.crono = obj.timing[obj.light];
  return obj;
}

modelState getState(){
  return state;
}

void setState(modelState newState){
  state = newState;
  render();
}

 
void setup() {
  setState(setDefault());// cargo los valores por defecto
}

void render(){
  //Renderizado del estado. representacion electrica del estado.
  if(state.mode == working){
    timer.run();
    if(state.light == red){
      ledR.on();
      ledY.off();
      ledG.off();
    }
    else if(state.light == redYellow){
      ledR.on();
      ledY.on();
      ledG.off();
    }
    else if(state.light == green){
      ledR.off();
      ledY.off();
      ledG.on();
    }
    else if(state.light == yellow){
      ledR.off();
      ledY.on();
      ledG.off();
    }
  }else if(state.mode == standby){
    // modo standby
      timer.clear();
      ledR.on();
      ledY.on();
      ledG.on();
  }
 }



void loop() {
  // controller
  timer.setTimeout([](){
    modelState copyState = getState();
    copyState.crono = copyState.crono - 1;
    if(copyState.crono == 0){
      copyState.light = copyState.light + 1;
      if(copyState.light == end){
        copyState.light = red;
      }
      copyState.crono = copyState.timing[copyState.light];
    }
    setState(copyState);
  },1000);
  
  button.addEventListener("keydown",[](){
    modelState copyState = getState();
    if(copyState.mode == working){
      copyState.mode = standby;
      setState(copyState);
    }else if(copyState.mode == standby){
      setState(setDefault());
    }
  });
}
