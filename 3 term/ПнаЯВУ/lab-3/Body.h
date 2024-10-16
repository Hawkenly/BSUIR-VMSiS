class Body {
protected:
    int number_of_doors;
    float size[3];
public:
    Body():number_of_doors(0),size{0.0,0.0,0.0}{};
    explicit Body(int ,float,float, float);

    int GetNumberOfDoors() const ;
    void SetNumberOfDoors(int);

    float* GetSize() ;
    void SetSize(float,float,float);

   // void Show();

    ~Body();
};

