FROM archlinux:latest

RUN pacman -Syu --noconfirm texlive-basic texlive-latex texlive-latexrecommended texlive-latexextra \
    texlive-xetex texlive-pictures texlive-mathscience texlive-bibtexextra \
    texlive-fontsrecommended texlive-fontutils \
    texlive-langcjk texlive-langchinese noto-fonts noto-fonts-cjk \
    biber make unzip

WORKDIR /work

COPY . .

RUN cd ttf && \
    unzip 'DMCAsansserif9.0-20252.zip' && \
    unzip 'Noto_Sans.zip' && \
    ls | grep .ttf | xargs -I% -n1 install -Dm644 % /usr/share/fonts/ttf/% 

RUN cd /work && mkdir -p /usr/share/fonts/otf && \
    cp /work/NotoSerifTC-Medium.otf /usr/share/fonts/otf/NotoSerifTC-Medium.otf 

RUN fc-cache -fv

CMD ["make"]
