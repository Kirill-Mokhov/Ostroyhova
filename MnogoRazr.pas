type Tlong=record
       countElem: integer;
       Long :  array [1..100] of string;
     end;
     
//..............................................................................Удаление ведущих нулей
procedure deliteZiro(var s:string; var checkZiro : boolean);
var i, numbNoZiro : integer;
begin
  for i := 1 to length(s) do
  begin
    if (s[i] = '0') and (checkZiro = true)
    then
      numbNoZiro := i
    else
      checkZiro := false
  end;
  Delete(s,1,numbNoZiro);
end;

//..............................................................................Процедура считывания числа
procedure ReadTLong(f1:text; var A:Tlong; var error:boolean);
var
  s, s1:string;
  i, EndLine, count, numbNoZiro:integer;
  checkZiro : boolean;  
begin
//..............................................................................Проверка на максимальное количество символов
  readln(f1, s);
  error := false;
  if length(s) > 300
  then
  begin
    writeln('Количество символов превышает максимум. (300 символов)');
    error:= true;
  end;
//..............................................................................Удаление ведущих нулей
  checkZiro := true;
  deliteZiro(s,checkZiro);
//..............................................................................Проверка на недопустимые символы
  for i := 1 to length(s) do
    if  not (s[i] in ['0'..'9','A','B','C','D','E','F'])
    then 
    begin
      writeln('Недопустимый символ "',s[i],'"');
      error := true;
    end;
//..............................................................................Деление на тройки и запись в массив
  s1 := '';
  EndLine := length(s);
  count := 0;
  if error = false
  then
  begin
    while EndLine > 0 do
    begin
      if EndLine >= 3
      then
      begin
        inc(count);
        s1 := Copy(s ,EndLine - 2, 3);
        A.Long[count] := s1;
        EndLine := EndLine - 3;
      end;
      if EndLine = 2
      then
      begin
        inc(count);
        s1 := Copy(s ,EndLine - 2, 2);
        A.Long  [count] := '0' + s1;
        EndLine := EndLine - 2;
      end;
      if EndLine = 1
      then
      begin
        inc(count);
        s1 := Copy(s ,EndLine - 1, 1);
        A.Long[count] := '00' + s1;
        EndLine := EndLine - 1;
      end;
    end;
    A.countElem := count;//Количество чисел занеcенных в массив
  end;
end;

//..............................................................................Печать числа
procedure writeTlong(A:Tlong);
var i, j : integer;
    s : string;
    checkZiro : boolean;
begin
  write('Число элементов в массиве "', A.countElem,'". ');
  checkZiro := true;
  for i := A.countElem downto 1 do
  begin
    deliteZiro(A.Long[i],checkZiro);
    write(A.Long[i]);
  end;
  writeln;
end;

//..............................................................................Перевод из char в integer
function CharInt(a:char):integer;
var
  x1,er:integer;
begin
  case a of
    'A': x1 := 10;
    'B': x1 := 11;
    'C': x1 := 12;
    'D': x1 := 13;
    'E': x1 := 14;
    'F': x1 := 15;
    '0'..'9': val(a,x1,er);
  end;
CharInt := x1;
end;
//..............................................................................Перевод из integer в char
function IntChar(a:integer):char;
var
  s:string;
begin
  s := '0123456789ABCDEF';
  IntChar := s[a+1];
end;

//..............................................................................Сложение первого числа элемента массива со вторым числом элемента массива
procedure add3TLong(first:string; second:string; var add:string; var ostatok:integer);
type ElementAdd=record
       ostatok: integer;
       sumChisel: integer;
     end;
var 
  matrica : array [0..15,0..15] of ElementAdd;
  i, j, sum, ostatokSUM:integer;
begin
//..............................................................................Заполнение матрицы сложения в 16-ой системе счисления
  for i := 0 to 15 do
    for j := 0 to 15 do
    begin
      matrica[i,j].ostatok := (i+j) div 16;
      matrica[i,j].sumChisel := (i+j) mod 16;
    end;
    add := '';
//..............................................................................Поразрядное сложение в тройках(элементы массива)
      for i := 3 downto 1 do 
      begin
        ostatokSUM := 0;
        sum := matrica[CharInt(first[i]),CharInt(second[i])].sumChisel + ostatok;
        if sum = 16
        then
          ostatokSUM := 1;
        add :=  IntChar(sum mod 16) + add;
        ostatok := matrica[CharInt(first[i]),CharInt(second[i])].ostatok + ostatokSUM;
      end;
end;

//..............................................................................Процедура добавление остатка в большее число
procedure addOstatokMass(A:Tlong;var add:Tlong; ostatokElem: integer);
var i : integer;
    sumElem : string;
begin
  for i := add.countElem + 1 to A.countElem do
  begin
    add3Tlong(A.Long[i], '000', sumElem, ostatokElem);
    add.Long[i] := sumElem;
    add.countElem := A.countElem;
  end;
  if (i = add.countElem) and (ostatokElem = 1)
  then
  begin
    inc(add.countElem);
    add.Long[add.countElem] := IntChar(ostatokElem);
  end;
end;

{||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||}
procedure addTLong(firstMass:Tlong; secondMass:Tlong; var addMass:Tlong);
var
  ostatokElem, countAdd , elementFirstMass, elementSecondMass, i, countWhile: integer;
  secondMassMore, equallyMass : boolean;
  sumElem : string;
begin
//..............................................................................Сравнение колличества элементов массивов 1 числа со 2
  if firstMass.countElem < secondMass.countElem
  then
  begin
    addMass.countElem := firstMass.countElem;
    secondMassMore := true;
  end
  else
  begin
    addMass.countElem := secondMass.countElem;
    secondMassMore := false;
  end;
//..............................................................................Если количество элементов одинаковое
  equallyMass := false;
  if firstMass.countElem = secondMass.countElem
  then
    equallyMass := true;
//..............................................................................Сложение элементов массивов
  for i := 1 to addMass.countElem do
  begin
    add3TLong(firstMass.Long[i], secondMass.Long[i], sumElem, ostatokElem);
    addMass.Long[i] := sumElem;
  end;
//..............................................................................Если количество элементов одинаково, но остался остаток от суммы
  if (ostatokElem = 1) and (equallyMass = true)
  then
  begin
    inc(addMass.countElem);
    addMass.Long[addMass.countElem] := IntChar(ostatokElem);
  end;
//..............................................................................Прибавление остатка если остались элементы в каком-то из массивов
  if (equallyMass = false)
  then
  begin
//..............................................................................Для второго числа
    if secondMassMore = true
    then
      addOstatokMass(secondMass,addMass, ostatokElem)
//..............................................................................Для первого числа
    else
      addOstatokMass(firstMass,addMass, ostatokElem)
  end;
end;

{
procedure 
var
begin

end;


procedure subTlong(A:Tlong;B:Tlong;var subMass:Tlong);
var
begin

end;
}

var
  f1:text;
  i, numbChisla:integer;
  firstMass, secondMass, addMass :Tlong;
  error:boolean;
begin
  assign(f1, 'chisla.txt');
  reset(f1);
  ReadTLong(f1, firstMass, error);
  ReadTLong(f1, secondMass, error);
  addTLong (firstMass, secondMass, addMass);
  writeTlong(firstMass);
  writeTlong(secondMass);
  writeTlong(addMass);
end.