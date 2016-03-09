# uniquify

_Generate a UUID with C++_

```
uniquify.generate(4, (err, result) => {
  /*
  {
    uuid: '3c87152c-64f4-4a33-924e-6cf31b606ae3',
    base62: '5CBcAoM2qv5-CYmgZGciXZb',
    uuidPretty: 'version=4,randbits=3c87152c64f40a33124e6cf31b606ae3,'
  }
  */
});
```

* `.generate` accepts two arguments
  * The version of the UUID you want, `0`, `1`, or `4`
  * The callback. 
