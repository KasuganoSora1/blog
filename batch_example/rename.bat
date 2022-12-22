@echo off
setlocal enabledelayedexpansion
rem 源文件为 .\F50G029004\GD_DLG_BOU_PY.dbf 将文件名更改为 .\F50G029004\F50G029004_BOU_PY.dbf
rem 文件夹中存在一个数据说明.txt，把它给避开
rem 最后根据F50G029004_BOU_PY中的BOU_PY把文件放入文件夹.\dst\BOU_PY中
for /d %%i in (G:\data_exec\ori\*) do (
    for %%j in (%%i\*) do (

        set file_full_path=%%j
        set file_path=%%~dpj
        set file_name=%%~nxj
        set file_noext_name=%%~nj
        set index=!file_path:~17,10!
        set is_txt=!file_full_path:~-3!
        set new_name=!index!_!file_name:~7!
        set label_6=!file_noext_name:~11,6!
        set label_4=!file_noext_name:~11,4!


        if not !is_txt! == txt (
            echo rename !file_full_path! !new_name!
            rename !file_full_path! !new_name!
        )
        for %%k in (BOU_PY,HYD_LN,HYD_PT,HYD_PY,LRD_LN,LRD_PT,LRD_PY,LRD_LN,LRD_PT,LRR_LN,LRR_PT,LRR_PY,RES_LN,RES_PT,RES_PY,TERL,TERP,TFCA,TFCL,TFCP,VEG_PY) do (
            if exist .\dst\%%k\ (
                if %%k == !label_6! (
                    echo copy !file_full_path! .\dst\%%k\!file_name!
                    copy !file_full_path! .\dst\%%k\!file_name!
                    echo del !file_full_path!
                    del !file_full_path!
                )
                if %%k == !label_4! (
                    echo copy !file_full_path! .\dst\%%k\!file_name!
                    copy !file_full_path! .\dst\%%k\!file_name!
                    echo del !file_full_path!
                    del !file_full_path!
                )
            )
        )


    )
)
