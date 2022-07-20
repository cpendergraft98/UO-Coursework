# Q3: Logic

Your experience with the Sudoku and 
Where's Waldo projects should help you 
tackle this one.  It asks you to check
whether *some* column of a matrix 
(lists of lists) contains *all* of the colors 
from another list of colors, called a spectrum. 

For example, suppose the spectrum is 
red, green, and blue, the primary colors. We 
might have 

```python
PRIMARIES = [ Color.red, Color.green, Color.blue ]
```

Then we might make a grid with three rows and 
three columns: 

```python
    grid = Grid(
        [[Color.red, Color.green, Color.blue]
        ,[Color.red, Color.blue, Color.green]
        ,[Color.green, Color.red, Color.blue]])
```
The second column (column 1) contains red, 
green, and blue tiles (although not in that 
order), so 
```python
grid.some_column_all_colors(PRIMARIES)
```
should return `True`.  However, if we changed the 
grid to 
```python
    grid = Grid(
        [[Color.red, Color.green, Color.blue]
        ,[Color.red, Color.green, Color.blue]
        ,[Color.green, Color.red, Color.blue]])
```
then `grid.some_column_all_colors()` should return 
`False`. 

You must finish the method `some_column_all_colors`.
