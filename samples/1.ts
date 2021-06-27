function printf(msg: string, value: int): void;

// function printf(msg: string, value: double): void;
// function printf(msg: string, value: string): void;

class A {
    x: int = 10;
    y: double;
    z: boolean;
    w: string = "hello";

    sayHello(): void {
        this.x = this.x * 100;
        printf("Hello World, %d", this.x);
    }

}

function main(): int {

    let b: A = new A();
    b.x = 20;

    try {
        b.sayHello();
    } catch (e: int) {

    }


    return 0;

}