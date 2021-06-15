function printf(formatString: int, params: int): void;

function getchar(): int;

function main(): int {

    printf("Enter the %s", "number.!");

    let n: int = getchar() - 48;

    printf("The input is %d", n);

    return 0;
}