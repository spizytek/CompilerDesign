section .text
global _start ; Make the _start label global (entry point for the program)

_start:
    ; Set up the arguments for bounded_dist
    movq $7, %rdi ; x = 7
    movq $3, %rsi ; y = 3

    ; Call the bounded_dist function
    call bounded_dist

    ; At this point, the result is in %rax
    ; Let's assume we want to exit with the result as the status code

    ; Move the result from %rax to %rdi (exit status)
    movq %rax, %rdi

    ; Exit the program
    movq $60, %rax ; sys_exit on x86_64 Linux/macOS
    syscall

; The bounded_dist function itself
bounded_dist:
    subq %rsi, %rdi ; x = x - y
    cmpq $0, %rdi
    jns label1 ; jump if not negative (x - y >= 0)
    negq %rdi ; x = -x
    label1:
    cmpq $10, %rdi
    jge label2 ; jump if x >= 10

    movq %rdi, %rax ; result = x
    jmp label3 ; jump to the end
    label2:
    movq $10, %rax ; result = 10
    label3:
    retq ; return result