



enum modelMode {
  };

struct modelState {
  };
  
modelState state; // creo la variable estado
  
modelState setDefault(){
  modelState obj;
  //define los valores por defecto del state
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
  //Renderizado del estado.
 }



void loop() {
  // controller
}
