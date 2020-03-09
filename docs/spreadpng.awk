BEGIN { FS="!" }
{
    subdir=".";
    for (i = 1; i < NF; i++) {
        subdir = subdir"/"$i;
        system ("mkdir -p \""subdir"\"");
    }
    oldfile = $0;
    gsub("[:!:]", "/", $0); 
    system("cp \""oldfile"\" \""$0"\"");
}

