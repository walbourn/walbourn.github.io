[CmdletBinding()]
    param (
        # Name
        [Parameter(Mandatory)]
        [string]
        $Name 
    )
    
    process {
        $Date = Get-Date -Format "yyyy-MM-dd"
        $Time = Get-Date -Format "HH:mm"
        $FileName = "$($date.ToString())-$($name.Replace(" ","-")).md"

        $Blog = New-Object -TypeName "System.Text.StringBuilder"
        [void]$Blog.Append("---`n") 
        [void]$Blog.Append("layout: post`n")
        [void]$Blog.Append("title: $Name`n") 
        [void]$Blog.Append("date: $Date $Time`n") 
        [void]$Blog.Append("author: Chuck Walbourn`n") 
        [void]$Blog.Append("comments: true`n") 
        [void]$Blog.Append("categories: [general]`n") 
        [void]$Blog.Append("---`n") 
        [void]$Blog.Append("`n<!--more-->`n")
        $Blog = $Blog.toString() 

        $NewBlogPath = Join-Path -ChildPath $FileName -Path "./_posts"

        Set-Content -Value $Blog -Path $NewBlogPath.tolower()
        Write-Output (Get-ChildItem $NewBlogPath.tolower())

        atom $NewBlogPath
    }
    
    end {
    }