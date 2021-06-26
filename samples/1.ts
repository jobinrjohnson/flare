// @ts-ignore
function printf(format: string, arg: int): void;

class SampleClass {
    hello: int = 0;

    say2hello(): void {
        // printf("The class number is %d", this.hello);
    }

    // sayHello(): int {
    //     // this.say2hello();
    //     printf("The class number is %d", this.hello)
    //     return this.hello;
    // }
}

// define dso_local i32 @_ZN1x5printEv(%class.x* nonnull dereferenceable(4) %0) #5 align 2 {
//     %this = alloca %A*, align 8
//     store %A* %0, %A** %this, align 8
//     %1 = load %A*, %A** %this, align 8
//     %2 = getelementptr inbounds %A, %A* %1, i32 0, i32 0
//     %3 = load i32, i32* %2, align 4
//     ret i32 %3
// }

// @ts-ignore
function main(): int {

    let x: SampleClass = new SampleClass();

    let i: int = 0;

    // x.say2hello();

    // printf("%d", x.hello);

    // let a: double = 90.3;
    // printf("The number is %f", a);

    return 0;
}