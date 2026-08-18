#include "engine.h"

int main(){

  eclipse::engine& engine = eclipse::engine::Instance();
  engine.Run();
  return 0;
}
