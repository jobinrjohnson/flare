class ClassName {
    i: int;
    j: float;
    k: double;
    l: boolean;

    a(m:int): boolean {
        console.log(m);
        return false;
    };
}

function main(): int {

    let l = new ClassName();
    // if (l.a()) {
    //     console.log("Hello world")
    // } else {
    //     console.log("There is no hello world!.")
    // }

    return 0;
}