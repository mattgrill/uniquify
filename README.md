# uniquify

_Generate a UUID with C++_

## async

```javascript
uniquify.generate(4, (err, result) => {
  /*
  3c87152c-64f4-4a33-924e-6cf31b606ae3
  */
});
```

* `.generate` accepts two arguments
  * The version of the UUID you want, `0`, `1`, or `4`
  * The callback. 

## sync

```javascript
uniquify.generateSync(4);
/*
3c87152c-64f4-4a33-924e-6cf31b606ae3
*/

```

* `.generate` accepts one argument
  * The version of the UUID you want, `0`, `1`, or `4`
