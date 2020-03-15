BEGIN { FS="!" }
{
    subdir=".";
    for (i = 1; i < NF; i++) {
        fragment = $i;
        gsub("[[:space:]]", "_", fragment);
        subdir = subdir"/"fragment;
        system ("mkdir -p \""subdir"\"");
    }
    oldfile = $0;
    gsub("[:!:]", "/", $0); 
    gsub("[[:space:]]", "_", $0);
    gsub(/_[0-9]+/, "", $0);
    system("cp \""oldfile"\" \""$0"\"");
}

