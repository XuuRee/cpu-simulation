# CPU 
Simulation of central processing unit instructions in C language.

## Stack (LIFO, abstract data type)
```
struct stack
{
    int32_t *values;
    int32_t *top;
};
```

```
void stackInit(struct stack *stack);
void stackClear(struct stack *stack);
void stackPush(struct stack *stack, int32_t cpu_register);
void stackPop(struct stack *stack);
```

## Running the program
```
./a.out -R
> mova 10
> push
> swac
> load
> dec
> swab
> sub
> run
# Registers -10 9 10 | Stack 10
> halt
```
