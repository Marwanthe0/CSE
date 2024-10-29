public class Inher {
    public static void main(String[] args) {
        System.out.println("Hello");
        animal ob = new animal();
        ob.setter(100);
        System.out.println(ob.getter());
    }
}

class animal {
    private int a = 5;

    void sound() {
        System.out.println("I am animal sound.\n");
    }

    void setter(int x) {
        this.a = x;
    }

    int getter() {
        return a;
    }
}

class cat extends animal {
}

class persian extends cat {
}
