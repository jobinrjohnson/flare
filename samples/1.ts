// @ts-ignore
function printf(format: string, arg: double): void;

class A {
    hello: int;
}

// @ts-ignore
function main(): int {

    let x: A = new A();

    let a: double = 90.3;
    printf("The number is %f", a);

    return 0;
}