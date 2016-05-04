# 24h
The 24 Hour Programming Language Interpreter - Interprets .24h Files
<br/>Created by Isaac Shelton on 5.3.2016

    Instruction List:
        '`' Allocate               Allocates number of cells               `(value).
        '~' Deallocate             Deallocates number of cells             ~(value).
        '^' Set Cell               Sets the cell number                    ^(value).
        '>' Increament Cell        Increaments the cell number             >(value).
        '<' Decreament Cell        Decreaments the cell number             <(value).
        '+' Add To                 Adds to the Current Cell                +(value).
        '-' Subtract From          Subtracts from the Current Cell         -(value).
        '=' Set                    Sets the value of the Current Cell      =(value).
        '!' Print                  Prints the value of the Current Cell    !
        '"' Input                  Inputs an Amount of Characters          "(value).
        '%' Not                    Logical Not of Current Cell value       %
        '&' Goto                   Jumps to that location in the file      &(value).
        '@' Conditional Goto       Jumps to that location if cell is 1     @(value).
        ':' Here                   Sets the Cell value to the Cell index   :
        ';' Current Cell           Sets a Cell to the current Cell index   ;(value).
        '#' Recall                 Sets the Cell index to the Cell value   #
        '?' Conditional            Evaluates depending on condition        ?(condition)(value).(result cell).
            '=' Checks for equality     ?=100.0.
            '<' Less Than               ?<100.0.
            '>' Greater Than            ?>100.0.
            '{' Less Than or Equal      ?{100.0.
            '}' Greater Than or Equal   ?}100.0.

            If result cell isn't a blank string, the result of the conditional will set the result cell to either 1 or 0
                For example: ?=100.8.
                If the current cell is 100, the cell 8 will be set to 1 otherwise it will be set to 0
            If result cell is a blank string, the result value will be placed into the current cell
                For example: ?=100..
                If the current cell is 100, the current cell will be set to 1 otherwise it will be set to 0
        '.' Terminator             Terminates a value

    hello.24h - example program:
        `1.^0.=72.!=101.!=108.!=108.!=111.!=32.!=87.!=111.!=114.!=108.!=100.!

    echo.24h  - example program:
        `255.^0."255.!>1.!?=0..%@14.
