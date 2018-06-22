nvprof -f -o nvvp\original.timeline.nvvp bin\Original.exe 0.xml 10
nvprof --analysis-metrics -f -o nvvp\original.analysis.nvvp bin\Original.exe 0.xml 10


nvprof -f -o nvvp\messageAware.timeline.nvvp bin\MessageAware.exe 0.xml 10
nvprof --analysis-metrics -f -o nvvp\messageAware.analysis.nvvp bin\MessageAware.exe 0.xml 10