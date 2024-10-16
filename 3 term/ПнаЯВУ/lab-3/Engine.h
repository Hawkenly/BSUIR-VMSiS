enum type{unknown,petrol,diesel,rotary,hybrid};

class Engine {
protected:
    type tp;
    float volume;
    int power;
public:
    Engine():tp(),volume(0.0),power(0){};
    explicit Engine(type,float,int);

    type GetTp();
    void SetTp(const char*);

    float GetVolume() const;
    void SetVolume(float);

    int GetPower() const;
    void SetPower(int);

   // void Show();

    ~Engine();
};


