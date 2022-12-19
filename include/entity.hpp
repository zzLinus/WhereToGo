class Entity {
public:
  Entity(){};
  virtual ~Entity(){};
  virtual void Render(){};

private:
public:
  int frameSpeed;
  int currentFrame;
  int frameCounter;

private:
};
