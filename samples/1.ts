function print(message: string): void;

// @ts-ignore
function read_int(): int;

function get_line(): string;


// @ts-ignore
function main(): int {
    print("Enter Your Name : ");
    let name: string = get_line();

    print("Enter Your Age : ");
    let age: int = read_int();

    let i:number;

    print("Your Name is ");
    print(name);
    print("You are ")

    if (age < 50) {
        print("Young");
    } else if (age < 100) {
        print("old");
    } else {
        print("too old to be alive");
    }

    return 0;
}