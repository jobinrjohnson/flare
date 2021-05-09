let b = 90;

function someFunctionName(i, j) {
    return i + j;
}

function main() {
    let sum = 0;
    let i = 0;

    while (i < 10) {
        i = i + 1;
        sum = sum + i;
        console.log(someFunctionName(i, sum));
    }
    return 0;
}
