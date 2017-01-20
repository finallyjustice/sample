Name:           helloc
Version:        0.1
Release:        1%{?dist}
Summary:        A hello world C program

Group:          Application
License:        GPL
#URL:            
Source0:        helloc-0.1.tar.gz

#BuildRequires:  
#Requires:       

%description
This is a sample rpm build test.

%prep
%setup -q


%build
gcc helloc.c -o helloc


%install
mkdir -p %{buildroot}/usr/local/bin
install -m 755 helloc %{buildroot}/usr/local/bin/helloc

#%clean
#rm -rf $RPM_BUILD_ROOT


%files
/usr/local/bin/helloc
