$ResultFile = "C:\JenkinsHome\workspace\PT_Trigger\CICD_NewResult0\CICD_NewResult0.lrr"
$OutputFile ="C:\JenkinsHome\workspace\LR_Output\Summary.html"

$AnalysisApp = New-Object -ComObject "Analysis.Api"

Write-Host "Opening Analysis session..."
$AnalysisApp.CreateSession($ResultFile)

Write-Host "Exporting summary to Excel....."
$AnalysisApp.ExportSumaryToExcel($OutputFile)

$AnalysisApp.CloseSession()
Write-Host "Done....."