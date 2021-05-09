function factorial(i) {
    if (i == 1) {
        return 1;
    }
    return i * factorial(i - 1);
}

function main() {
    let i = 0;

    while (i < 10) {
        i = i + 1;
        console.log(0);
        console.log(i);
        console.log(factorial(i));
    }
    return 0;
}
