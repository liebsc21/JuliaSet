Coding Challenge: Julia set
===

The coding challenge for this term's Computing Cafe is to provide the fastest possible implementation of the calculation of a [Julia set](https://en.wikipedia.org/wiki/Julia_set) in either C++ or Python (or both). We'll focus on a Julia set with a function of the form:

```
f(z) = z ^ n + r * exp(i * phi).
```


The animation will be created for ```N``` steps with angles phi uniformly distributed in ```[0,2 pi)```. For each step a csv file has to be written for each step of the animation (i.e. each fixed angle), containing the values in ```gridwidth``` points in both coordinates of the complex plane for ```-1.8 < x < 1.8``` (same for ```y```). The csv should store the number of iterations after which the cut-off condition ```|z| > 2.0``` is fulfilled for each point. A cut-off after 300 iterations is to be applied.

The free parameters we'll choose at random, after the deadline are:
- ```n``` in the julia function
- ```r``` in the julia function
- ```N```: number of steps for the animation
- ```gridwidth```: number of steps for both x and y

An (very slow) example implementation can be found in [example.py](example.py). The script [plot_result.py](plot_result.py) will read in the csv files and create an animation from that.
