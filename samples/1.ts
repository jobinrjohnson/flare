let b = 90;

function main() {
    let sum = 0;
    let a = 1;

    while (a < b) {

        if (a <= 10) {
            if (a < 5) {
                console.log(sum);
            }
            console.log(10000);
        } else {
            console.log(0);
        }

        sum = sum + a;
        a = a + 1;
    }
    console.log(sum);
    return 0;
}
