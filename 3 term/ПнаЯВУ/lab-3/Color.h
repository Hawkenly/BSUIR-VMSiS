class Color {
protected:
    char color[255];
public:
    Color():color{"Неизвестно"}{};
    explicit Color(const char*);

    char* GetColor();
    void SetColor(const char*);

   // void Show();

    ~Color();

};
