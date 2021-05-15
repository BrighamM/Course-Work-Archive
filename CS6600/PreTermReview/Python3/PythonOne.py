# remember the first is included the last is excluded: 
# Note how the start is always included, and the end always excluded. This makes sure that s[:i] + s[i:] is always equal to s:
mylist = ["b","u","g"]
mylist[1] = "i"
print(mylist)


# Always use keyword only arguments, then you are sure of what you are passing


