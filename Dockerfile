FROM archlinux:latest

RUN echo 'ParallelDownloads = 5' >> /etc/pacman.conf

RUN pacman -Syu --noconfirm reflector rsync

RUN rm /etc/pacman.d/mirrorlist && \
    reflector -f 10 -c Taiwan >> /etc/pacman.d/mirrorlist

RUN pacman -S --noconfirm texlive-basic texlive-latex texlive-latexrecommended texlive-latexextra \
    texlive-xetex texlive-pictures texlive-mathscience texlive-bibtexextra \
    texlive-fontsrecommended texlive-fontutils texlive-langcjk texlive-langchinese \
    biber make unzip

RUN rm -rf /var/cache/pacman/pkg/* /var/lib/pacman/sync/* /tmp/* /var/tmp/*

WORKDIR /work

COPY main.tex .
COPY Makefile .
COPY code/ ./code/
COPY ttf/ ./ttf/
COPY NotoSerifTC-Medium.otf ./

RUN cd ttf && \
    unzip 'DMCAsansserif9.0-20252.zip' && \
    unzip 'Noto_Sans.zip' && \
    ls | grep .ttf | xargs -I% -n1 install -Dm644 % /usr/share/fonts/ttf/% 

RUN cd /work && mkdir -p /usr/share/fonts/otf && \
    cp /work/NotoSerifTC-Medium.otf /usr/share/fonts/otf/NotoSerifTC-Medium.otf 

RUN fc-cache -fv

CMD ["make"]
