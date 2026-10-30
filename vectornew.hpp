class Vector2D{
    private:
    double x;
    double y;

    public:
    Vector2D();

    Vector2D(double a, double b);

    double getMagnitude() const;

    Vector2D operator+(const Vector2D & rhs);

    Vector2D & operator+=(const Vector2D & rhs);

    double dot(const Vector2D & rhs) const;

    void print()const;
};