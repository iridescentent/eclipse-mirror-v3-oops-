#include "engine.h"
#include "app.h"

eclipse::App* CreateApp();
int main(){
  eclipse::App* app = CreateApp();
  eclipse::engine::Instance().Run(app);
  delete app;
  return 0;
}
