
### Controller Text How to Use

Controller text is set with a row, a starting column, length of total string and a label string + a value. value is converted into string automatically to fill void. This allows you to section off arreas of the controller screen into blocks to ensure there is no overcrowding

ex:
```
- - - - - - - - - - - -
| s p e e d : _ 1 0 0 |		controllerText.setText(0, 0, 10, "speed: ", 100);
- - - - - - - - - - - -
^ a block of size 10

- - - - - - - - - - - -
| s p e e d : _ _ 8 0 |		controllerText.setText(0, 0, 10, "speed: ", 80);
- - - - - - - - - - - -
^ a block of size 10

- - - - - - - - - - - -
| s p e e d : _ _ _ 7 |		controllerText.setText(0, 0, 10, "speed: ", 7);
- - - - - - - - - - - -
^ a block of size 10
```

line: 0-2

col: 0-18

length: 1-18 *MUST BE GREATER THAN LABEL LEN AND LESS THAN (18 - col)
