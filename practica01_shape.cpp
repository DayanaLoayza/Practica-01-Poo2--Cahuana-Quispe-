#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <stdexcept>
using namespace std;

struct Shape {
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual string type() const = 0; // Método adicional para identificación
};

class Rectangle : public Shape {
private:
    static constexpr double MIN_DIMENSION = 0.0;
    double width_, height_;
    
    void validateDimensions(double w, double h) {
        if (w <= MIN_DIMENSION || h <= MIN_DIMENSION) {
            throw invalid_argument("Rectangle dimensions must be positive");
        }
    }
    
public:
    Rectangle(double width, double height) : width_(width), height_(height) {
        validateDimensions(width_, height_);
    }
    
    double area() const override { 
        return width_ * height_; 
    }
    
    double perimeter() const override { 
        static constexpr int PERIMETER_MULTIPLIER = 2;
        return PERIMETER_MULTIPLIER * (width_ + height_); 
    }
    
    string type() const override { 
        return "Rectangle"; 
    }
    
    // Observadores adicionales
    double width() const noexcept { return width_; }
    double height() const noexcept { return height_; }
};

class Circle : public Shape {
private:
    static constexpr double MIN_RADIUS = 0.0;
    double radius_;
    
    void validateRadius(double r) {
        if (r <= MIN_RADIUS) {
            throw invalid_argument("Circle radius must be positive");
        }
    }
    
public:
    explicit Circle(double radius) : radius_(radius) {
        validateRadius(radius_);
    }
    
    double area() const override { 
        return M_PI * radius_ * radius_; 
    }
    
    double perimeter() const override { 
        static constexpr int CIRCUMFERENCE_MULTIPLIER = 2;
        return CIRCUMFERENCE_MULTIPLIER * M_PI * radius_; 
    }
    
    string type() const override { 
        return "Circle"; 
    }
    
    // Observador adicional
    double radius() const noexcept { return radius_; }
};

// Función auxiliar para formatear salida
void displayShapeInfo(const Shape& shape) {
    cout << shape.type() << " - Area: " << shape.area() 
         << ", Perimeter: " << shape.perimeter() << '\n';
}

int main() {
    try {
        vector<unique_ptr<Shape>> shapes;
        
        // Creación de formas con valores de prueba documentados
        shapes.emplace_back(make_unique<Rectangle>(4.0, 3.0)); // Rectángulo 4x3
        shapes.emplace_back(make_unique<Circle>(2.5));          // Círculo radio 2.5
        shapes.emplace_back(make_unique<Rectangle>(5.0, 5.0)); // Cuadrado 5x5
        shapes.emplace_back(make_unique<Circle>(1.0));          // Círculo unitario
        
        cout << "=== Información de Formas Geométricas ===\n";
        
        for (const auto& shape : shapes) {
            displayShapeInfo(*shape);
        }
        
        // Cálculo de totales
        double totalArea = 0.0;
        double totalPerimeter = 0.0;
        
        for (const auto& shape : shapes) {
            totalArea += shape->area();
            totalPerimeter += shape->perimeter();
        }
        
        cout << "\n=== Resumen ===\n";
        cout << "Total formas: " << shapes.size() << '\n';
        cout << "Área total: " << totalArea << '\n';
        cout << "Perímetro total: " << totalPerimeter << '\n';
        
        // Prueba de validación (descomentar para probar excepciones):
        // auto invalidRect = make_unique<Rectangle>(-1.0, 2.0);
        // auto invalidCircle = make_unique<Circle>(0.0);
        
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    
    return 0;
}
