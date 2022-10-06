use std::f64::consts::PI;

fn main() -> () {
    let cl = |a: i32| a / 2;
    let tr = Triangle::new(3., 4., 5.);
    let p: f64 = match tr.area() {
        Some(x) => x,
        None => 0.,
    };
    print!("{}", p);
    let s: Shape = Shape::Triangle(3., 4., 5.);
    let q = (5, 'c', true);
}
struct Triangle {
    a: f64,
    b: f64,
    c: f64,
}
impl Triangle {
    fn new(a: f64, b: f64, c: f64) -> Self {
        Triangle { a, b, c }
    }
    fn area(&self) -> Option<f64> {
        if self.a < self.b + self.c && self.b < self.a + self.c && self.c < self.a + self.b {
            let s = (self.a + self.b + self.c) * 0.5;
            return Some((s * (s - self.a) * (s - self.b) * (s - self.c)).sqrt());
        }
        None
    }
    fn bigger<'a>(&'a self, other: &'a Self) -> &'a Self {
        let ar1 = match self.area() {
            Some(x) => x,
            None => 0.,
        };
        let ar2 = match other.area() {
            Some(x) => x,
            None => 0.,
        };
        if ar1 <= ar2 {
            return &other;
        }
        &self
    }
}
struct Circle {
    r: f64,
}
impl Circle {
    fn new(r: f64) -> Self {
        Circle { r }
    }
    fn area(&self) -> Option<f64> {
        if self.r > 0. {
            return Some(self.r * self.r * PI);
        }
        None
    }
}
enum Shape {
    Triangle(f64, f64, f64),
    Circle(f64),
}
struct Square {
    s: f64,
}
