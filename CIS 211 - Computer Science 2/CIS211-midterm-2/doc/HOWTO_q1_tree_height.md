# Q1:  Reaching for tomatoes

In software we usually draw trees upside 
down, but for this problem I will draw 
binary fruit trees right side up, for 
biological accuracy.  We will consider 
binary tomato trees in particular. 

The most important property of fruit trees 
is whether we can reach the fruit.
Our fruit trees
therefore need a method, `min_height`, 
that determines the shortest distance from
the root of the tree to any fruit. 
For example, this tree

```python
Branch(Branch(Fruit("tomato"), Fruit("tomato")),
       Branch(Fruit("tomato"), Fruit("tomato")))
``` 
has a minimum height of 2, as shown in this 
artist's rendering: 

![Bush tomato tree](img/tree-bushy-2.png)

On the other hand, this tree

```python
Branch(Branch(Fruit("tomato"), Fruit("tomato")),
Fruit("tomato"))
```
which we can draw as 

![Tree skewed left](img/tree-2-1.png)

has a minimum height of 1.  Although some 
tomatoes are higher up, there is a 
tomato that is only 1 branch away from the
ground.  

A tomato that has fallen off the tree and
is just laying on the ground is, of 
course, at height 0. 

Your job is to fill in the `min_height` 
methods so that we choose trees with 
reachable fruit.  



