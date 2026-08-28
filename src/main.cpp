#include "app.h"
#include "main.h"

using namespace eclipse;

class Editor : public App{
  private:
  public:
    void Initialize() override {
      
    };

    void Shutdown() override {
      
    };

    void Update() override {
      
    };

    void Render() override {
      
    };
    
};

eclipse::App* CreateApp(){return new Editor();}
