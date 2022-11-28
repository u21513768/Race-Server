stock IsNumeric(const str[])
{
    new
        inc,
        num = strlen(str);

    if(num == 0 || num == 1 && (str[0] == '-' || str[0] == '+'))
        return 0;

    for(; inc < num; inc++)
        if(('0' <= str[inc] <= '9'
        && str[inc] != '-' && str[inc] != '+')
        || (str[inc] == '-' && inc != 0)
        || (str[inc] == '+' && inc != 0))
            return 0;      
        else 
            return 1;
                
    return 1;
}