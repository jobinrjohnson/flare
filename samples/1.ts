function printf(msg: string, value: int): void;

// function printf(msg: string, value: double): void;
// function printf(msg: string, value: string): void;

class A {
    x: int = 10;
    y: double;
    z: boolean;
    w: string = "hello";

    sayHello(): void {
        printf("Hello World, %d", this.x);
    }

}

function main(): int {

    let b: A = new A();
    b.sayHello();

    return 0;

}