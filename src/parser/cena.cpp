typedef struct DATA {
    int width;
    int height;
} Data;

int Prop1(int thread_id,Data data){
  int a=0;
  int b=0;
  int c=0;
  int d=0;

  if(a && b> 1)
    return Prop2;
  if(b+1 > 0) {

    if(!(c+1) && d)
      return Prop3;

    return Prop4;
  }
  return FAIL;
}


int Prop2(int thread_id, Data data){
  int a=0;
  int b=0;
  int c=0;
  int d=0;

  if(a && b> 1)
    return Prop2;
  if(b+1 > 0) {

    if(!c && d)
      return Prop3;

    else
      return Prop4;
  }

  return FAIL;
}
